import styled from "styled-components";
import { useState, useEffect } from "react";
import Header from "./components/Header";
import FavoriteItemForm from "./components/FavoriteItemForm";
import FavoriteItemList from "./components/FavoriteItemList";
import FavoriteItemFilter from "./components/FavoriteItemFilter";
import { movieApi } from './api/movieApi';

const App = ({ className }) => {
  const [favoriteMovies, setFavoriteMovies] = useState([]);
  const [filterText, setFilterText] = useState("");

  useEffect(() => {
    const fetchMovies = async () => {
      try {
        const data = await movieApi.getAllMovies();
        setFavoriteMovies(data);
      } catch (error) {
        console.error('Error fetching movies:', error);
      }
    };
    fetchMovies();
  }, []);

  const handleFilterChange = (text) => {
    setFilterText(text);
  };

  const isDuplicateTitle = (title, excludeId = null) => {
    return favoriteMovies.some(
      (movie) =>
        movie.title.toLowerCase() === title.toLowerCase() &&
        movie.id !== excludeId,
    );
  };

  const addFavoriteMovie = async (title, url) => {
    if (isDuplicateTitle(title)) {
      alert("This movie is already in your favorites!");
      return;
    }

    const newMovie = {
      title,
      genre: "Unknown",
      url,
      color: getRandomColor(),
    };

    try {
      const createdMovie = await movieApi.createMovie(newMovie);
      setFavoriteMovies([...favoriteMovies, createdMovie]);
    } catch (error) {
      console.error('Error adding movie:', error);
    }
  };

  const handleTitleChange = async (id, newTitle) => {
    if (isDuplicateTitle(newTitle, id)) {
      alert("This title already exists in your favorites!");
      return;
    }

    try {
      const updatedMovie = await movieApi.updateMovie(id, { title: newTitle });
      setFavoriteMovies(
        favoriteMovies.map((movie) =>
          movie.id === id ? updatedMovie : movie
        ),
      );
    } catch (error) {
      console.error('Error updating movie:', error);
    }
  };

  const getRandomColor = () => {
    const colors = [
      "crimson", "forestgreen", "dodgerblue", "mediumorchid",
      "chocolate", "darkorange", "steelblue", "seagreen",
      "slateblue", "tomato", "teal", "indianred",
    ];
    return colors[Math.floor(Math.random() * colors.length)];
  };

  const handleDelete = async (id) => {
    if (window.confirm("Are you sure you want to delete this movie?")) {
      try {
        await movieApi.deleteMovie(id);
        setFavoriteMovies(favoriteMovies.filter((movie) => movie.id !== id));
      } catch (error) {
        console.error('Error deleting movie:', error);
      }
    }
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
        onTitleChange={handleTitleChange}
        onDelete={handleDelete}
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
    background-color: #d0d0d0;
    padding: 2px 5px;
    border-radius: 3px;
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

export default StyledApp;
