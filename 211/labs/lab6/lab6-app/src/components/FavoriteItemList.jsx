import FavoriteItem from "./FavoriteItem";

const FavoriteItemList = ({ favoriteMovies, filterText }) => {
  const filteredMovies = favoriteMovies.filter((movie) =>
    movie.title.toLowerCase().includes(filterText.toLowerCase()),
  );

  return (
    <div id="favorite-movies">
      <h3>List:</h3>
      <ol>
        {filteredMovies.map((movie) => (
          <FavoriteItem key={movie.id} {...movie} />
        ))}
      </ol>
    </div>
  );
};

export default FavoriteItemList;
