import styled from "styled-components";
import { useState } from "react";
import { BadgeX } from "lucide-react";

const StyledListItem = styled.li`
  display: inline-flex;
  align-items: center;
  gap: 10px;
  padding: 4px 16px;
  margin: 2px 0;
  border-radius: 4px;
  color: ${(props) => props.color};
  background-color: ${(props) => props.color}22;
  transition: background-color 0.2s ease;
  width: fit-content;
  max-width: 100%;

  &:hover {
    background-color: ${(props) => props.color}33;
  }

  span {
    color: ${(props) => props.color};
    white-space: nowrap;
  }
`;

const StyledLink = styled.a`
  color: #2563eb;
  text-decoration: none;
  padding: 4px 8px;
  border-radius: 4px;
  background-color: #dbeafe;
  transition: all 0.2s ease;
  white-space: nowrap;

  &:hover {
    background-color: #bfdbfe;
    transform: translateY(-1px);
    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  }

  &:active {
    transform: translateY(0);
    box-shadow: none;
  }
`;

const DeleteIconWrapper = styled.div`
  position: relative;
  margin-left: auto;
  padding: 5px;
  cursor: pointer;

  .delete-icon {
    color: #ff4444;
    transition: all 0.2s ease;
    animation: breathe 2s infinite ease-in-out;
  }

  @keyframes breathe {
    0% {
      transform: scale(1);
    }
    50% {
      transform: scale(1.2);
    }
    100% {
      transform: scale(1);
    }
  }

  &:hover .delete-icon {
    animation: none;
    transform: scale(1.1);
    filter: brightness(0.8);
  }

  &:hover > div {
    visibility: visible;
    opacity: 1;
  }
`;

const DeleteTooltip = styled.div`
  visibility: hidden;
  opacity: 0;
  position: absolute;
  background-color: #333;
  color: white;
  padding: 4px 8px;
  border-radius: 4px;
  font-size: 12px;
  white-space: nowrap;
  top: -25px;
  left: 50%;
  transform: translateX(-50%);
  transition: all 0.2s ease;

  &:after {
    content: "";
    position: absolute;
    top: 100%;
    left: 50%;
    margin-left: -5px;
    border-width: 5px;
    border-style: solid;
    border-color: #333 transparent transparent transparent;
  }
`;

const FavoriteItem = ({ id, title, url, color, onTitleChange, onDelete }) => {
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
    <StyledListItem color={color}>
      {isEditing ? (
        <input
          type="text"
          value={editedTitle}
          onChange={handleChange}
          onBlur={handleSave}
          onKeyPress={handleKeyPress}
          autoFocus
          style={{ width: "40%" }}
        />
      ) : (
        <span onDoubleClick={handleDoubleClick}>{title}</span>
      )}
      <StyledLink href={url} target="_blank" rel="noopener noreferrer">
        {new URL(url).hostname}
      </StyledLink>
      <DeleteIconWrapper>
        <BadgeX
          size={18}
          onClick={() => onDelete(id)}
          className="delete-icon"
        />
        <DeleteTooltip>Delete</DeleteTooltip>
      </DeleteIconWrapper>
    </StyledListItem>
  );
};

export default FavoriteItem;
