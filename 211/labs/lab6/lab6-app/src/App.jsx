import styled from "styled-components";
import { useState } from "react";
import Header from "./components/Header";
import FavoriteItemForm from "./components/FavoriteItemForm";
import FavoriteItemList from "./components/FavoriteItemList";
import FavoriteItemFilter from "./components/FavoriteItemFilter";

const App = ({ className }) => {
  const [favoriteMovies, setFavoriteMovies] = useState([
    {
      id: 0,
      title: "The Dark Knight",
      genre: "Action",
      url: "https://www.imdb.com/title/tt0468569/",
      color: "brown",
    },
    {
      id: 1,
      title: "The Godfather",
      genre: "Crime",
      url: "https://www.imdb.com/title/tt0068646/",
      color: "red",
    },
    {
      id: 2,
      title: "The Lord of the Rings: The Return of the King",
      genre: "Action",
      url: "https://www.imdb.com/title/tt0167261/",
      color: "blue",
    },
  ]);
  const [filterText, setFilterText] = useState("");

  const getRandomColor = () =>
    ["brown", "red", "blue", "green", "purple", "orange"][
      Math.floor(Math.random() * 6)
    ];

  const addFavoriteMovie = (title, url) => {
    setFavoriteMovies(
      favoriteMovies.concat({
        id: favoriteMovies.length,
        title,
        genre: "Unknown",
        url,
        color: getRandomColor(),
      }),
    );
  };

  const handleFilterChange = (text) => {
    setFilterText(text);
  };

  return (
    <div className={className}>
      <StyledTitle>Favorite Movies</StyledTitle>
      <Header />
      <FavoriteItemForm addFavoriteMovie={addFavoriteMovie} />
      <FavoriteItemFilter onFilterChange={handleFilterChange} />
      <FavoriteItemList
        favoriteMovies={favoriteMovies}
        filterText={filterText}
      />
    </div>
  );
};

const StyledApp = styled(App)`
  border: 3px solid #000;
  width: 650px;
  padding: 0 25px 25px 25px;
  margin: 25px auto;
  background-color: #a3d4ff;
  font-family: Arial, sans-serif;
  color: #333;
  text-align: center;

  h1 {
    font-size: 2.5rem;
    font-weight: bold;
    color: navy;
    margin: 0;
  }

  h3 {
    font-size: 1.2rem;
    color: #333;
  }

  #favorite-movies {
    margin-top: 20px;
  }

  ol {
    list-style-type: none;
    padding: 0;
  }

  li {
    background-color: #e0f2ff;
    border-radius: 5px;
    padding: 10px;
    margin: 5px 0;
    display: flex;
    justify-content: space-between;
    align-items: center;
    font-size: 1rem;
  }

  a {
    text-decoration: none;
  }

  a:hover {
    text-decoration: underline;
  }
`;

const StyledTitle = styled.h1`
  font-size: 30pt;
  color: navy;
  margin-bottom: -10px;
`;

const StyledListItem = styled.li`
  padding: 10px;
  margin: 10px 0;
  border-radius: 5px;
  background-color: rgba(255, 255, 255, 0.5);
  list-style: none;
  font-family: sans-serif;
  color: ${(props) => props.color};
`;

const StyledLegend = styled.legend`
  font-weight: bold;
  color: navy;
  padding: 5px;
`;

const StyledLabel = styled.label`
  font-weight: bold;
  color: navy;
  padding: 5px;
`;

const StyledButton = styled.button`
  width: auto;
  padding: 10px 20px;
  background-color: #ccc;
  border: none;
  border-radius: 5px;
  cursor: pointer;
  font-size: 1rem;

  &:hover {
    background-color: green;
  }
`;

export default StyledApp;
