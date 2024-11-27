import FavoriteItem from "./FavoriteItem";
import styled from 'styled-components';
import { useMovies } from '../MovieContext';

const FavoriteItemList = () => {
  const { favoriteMovies, filterText, handleTitleChange, handleDelete } = useMovies();

  if (!favoriteMovies) {
    return <div>Loading...</div>;
  }

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
            onTitleChange={handleTitleChange}
            onDelete={handleDelete}
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
