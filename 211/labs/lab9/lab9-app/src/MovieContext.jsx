import { createContext, useContext, useState, useEffect } from 'react';
import { movieApi } from './api/movieApi';

const MovieContext = createContext();

export function MovieProvider({ children }) {
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

  const getRandomColor = () => {
    const colors = [
      "crimson", "forestgreen", "dodgerblue", "mediumorchid",
      "chocolate", "darkorange", "steelblue", "seagreen",
      "slateblue", "tomato", "teal", "indianred",
    ];
    return colors[Math.floor(Math.random() * colors.length)];
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

  const value = {
    favoriteMovies,
    filterText,
    handleFilterChange,
    addFavoriteMovie,
    handleTitleChange,
    handleDelete
  };

  return (
    <MovieContext.Provider value={value}>
      {children}
    </MovieContext.Provider>
  );
}

export function useMovies() {
  return useContext(MovieContext);
} 