import { useState } from "react";
import { 
  ListItem, 
  TextField, 
  IconButton, 
  Link, 
  Box,
  Tooltip
} from '@mui/material';
import { Delete } from '@mui/icons-material';

const FavoriteItemMUI = ({ id, title, url, color, onTitleChange, onDelete }) => {
  const [isEditing, setIsEditing] = useState(false);
  const [editedTitle, setEditedTitle] = useState(title);

  const handleDoubleClick = () => {
    setIsEditing(true);
  };

  const handleChange = (e) => {
    setEditedTitle(e.target.value);
  };

  const handleSave = () => {
    setIsEditing(false);
    if (editedTitle.trim()) {
      onTitleChange(id, editedTitle);
    } else {
      setEditedTitle(title);
    }
  };

  const handleKeyPress = (e) => {
    if (e.key === "Enter") {
      handleSave();
    }
  };

  return (
    <ListItem
      sx={{
        gap: 2,
        bgcolor: `${color}22`,
        color: color,
        borderRadius: 1,
        my: 0.5,
        width: 'auto',
        minWidth: '60%',
        '&:hover': {
          bgcolor: `${color}33`,
        }
      }}
    >
      {isEditing ? (
        <TextField
          value={editedTitle}
          onChange={handleChange}
          onBlur={handleSave}
          onKeyPress={handleKeyPress}
          autoFocus
          size="small"
          sx={{ width: "40%" }}
        />
      ) : (
        <Box 
          component="span" 
          onDoubleClick={handleDoubleClick}
          sx={{ whiteSpace: 'nowrap' }}
        >
          {title}
        </Box>
      )}
      
      <Link 
        href={url} 
        target="_blank" 
        rel="noopener noreferrer"
        sx={{
          bgcolor: '#dbeafe',
          px: 1,
          py: 0.5,
          borderRadius: 1,
          textDecoration: 'none',
          '&:hover': {
            bgcolor: '#bfdbfe',
            transform: 'translateY(-1px)',
            boxShadow: '0 2px 4px rgba(0,0,0,0.1)'
          }
        }}
      >
        {new URL(url).hostname}
      </Link>

      <Tooltip title="Delete">
        <IconButton 
          onClick={() => onDelete(id)}
          sx={{ 
            color: '#ff4444',
            ml: 'auto',
            '&:hover': {
              transform: 'scale(1.1)'
            }
          }}
        >
          <Delete />
        </IconButton>
      </Tooltip>
    </ListItem>
  );
};

export default FavoriteItemMUI; 