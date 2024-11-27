import axios from 'axios';

const BASE_URL = import.meta.env.VITE_API_BASE_URL;

export const movieApi = {
  // Read all movies
  getAllMovies: async () => {
    try {
      const { data } = await axios.get(`${BASE_URL}/movies`);
      return data;
    } catch (error) {
      console.error('Error fetching movies:', error);
      throw error;
    }
  },

  // Create new movie
  createMovie: async (movie) => {
    try {
      const { data } = await axios.post(`${BASE_URL}/movies`, movie);
      return data;
    } catch (error) {
      console.error('Error creating movie:', error);
      throw error;
    }
  },

  // Update movie
  updateMovie: async (id, updates) => {
    try {
      const { data } = await axios.patch(`${BASE_URL}/movies/${id}`, updates);
      return data;
    } catch (error) {
      console.error('Error updating movie:', error);
      throw error;
    }
  },

  // Delete movie
  deleteMovie: async (id) => {
    try {
      await axios.delete(`${BASE_URL}/movies/${id}`);
      return id;
    } catch (error) {
      console.error('Error deleting movie:', error);
      throw error;
    }
  }
}; 