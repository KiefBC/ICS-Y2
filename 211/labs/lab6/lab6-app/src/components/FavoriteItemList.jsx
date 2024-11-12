import FavoriteItem from "./FavoriteItem";
import styled from 'styled-components';

const FavoriteItemList = ({ favoriteMovies, filterText, onTitleChange, onDelete }) => {
  const filteredMovies = filterText === "" 
    ? favoriteMovies 
    : favoriteMovies.filter((movie) =>
        movie.title.toLowerCase().includes(filterText.toLowerCase())
      );

  return (
    <ListContainer>
      <StyledList>
        {filteredMovies.map((movie) => (
          <FavoriteItem 
            key={movie.id} 
            {...movie} 
            onTitleChange={onTitleChange}
            onDelete={onDelete}
          />
        ))}
      </StyledList>
    </ListContainer>
  );
};

const ListContainer = styled.div`
  width: 100%;
  max-width: 1200px;
  margin: 0 auto;
  padding: 0 20px;
`;

const StyledList = styled.ol`
  list-style-position: inside;
  padding: 0;
  margin: 5px 0;
  display: flex;
  flex-direction: column;
  align-items: center;
  
  li {
    margin: 3px 0;
  }
`;

export default FavoriteItemList;
