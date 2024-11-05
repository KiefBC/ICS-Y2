import styled from "styled-components";
import { useState } from "react";

const FavoriteItem = ({ id, title, genre, url, color, onTitleChange }) => {
  const [isEditing, setIsEditing] = useState(false);
  const [editedTitle, setEditedTitle] = useState(title);

  // Enable edit mode on double-click
  const handleDoubleClick = () => {
    setIsEditing(true);
  };

  // Handle title change input
  const handleChange = (e) => {
    setEditedTitle(e.target.value);
  };

  // Save the edited title and exit edit mode
  const handleSave = () => {
    setIsEditing(false);
    if (editedTitle.trim()) {
      onTitleChange(id, editedTitle);
    } else {
      setEditedTitle(title); // Revert to the original title if input is empty
    }
  };

  // Save title on Enter key press
  const handleKeyPress = (e) => {
    if (e.key === "Enter") {
      handleSave();
    }
  };

  return (
    <StyledListItem color={color}>
      {isEditing ? (
        <input
          type="text"
          value={editedTitle}
          onChange={handleChange}
          onBlur={handleSave}
          onKeyPress={handleKeyPress}
          autoFocus
          style={{ width: "70%" }}
        />
      ) : (
        <span onDoubleClick={handleDoubleClick}>
          {title} ({genre}):
        </span>
      )}
      <a href={url}>{url}</a>
    </StyledListItem>
  );
};

const StyledListItem = styled.li`
  padding: 10px;
  margin: 10px 0;
  border-radius: 5px;
  background-color: rgba(255, 255, 255, 0.5);
  list-style: none;
  font-family: sans-serif;
  color: ${(props) => props.color};
`;

export default FavoriteItem;
