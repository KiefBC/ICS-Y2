import styled from "styled-components";

const FavoriteItem = ({ title, genre, url, color }) => {
  return (
    <StyledListItem color={color}>
      {title} ({genre}): <a href={url}>{url}</a>
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
