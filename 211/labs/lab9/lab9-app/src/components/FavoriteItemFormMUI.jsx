import { useState } from "react";
import { useMovies } from "../MovieContext";
import { useNavigate } from "react-router-dom";
import {
  TextField,
  Button,
  Box,
  Paper,
  Typography,
  Container,
} from "@mui/material";

const FavoriteItemFormMUI = () => {
  const navigate = useNavigate();
  const { addFavoriteMovie } = useMovies();
  const [formData, setFormData] = useState({ title: "", url: "" });

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData((prevData) => ({
      ...prevData,
      [name]: value,
    }));
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    addFavoriteMovie(formData.title, formData.url);
    setFormData({ title: "", url: "" });
    navigate("/");
  };

  const isFormIncomplete = !formData.title || !formData.url;

  return (
    <Container maxWidth="md">
      <Paper elevation={3} sx={{ p: 3, my: 2 }}>
        <Box component="form" onSubmit={handleSubmit}>
          <Typography variant="h6" color="primary" gutterBottom>
            Add a Movie:
          </Typography>

          <Box sx={{ display: "flex", flexDirection: "column", gap: 2 }}>
            <TextField
              label="Title"
              name="title"
              value={formData.title}
              onChange={handleChange}
              fullWidth
              required
              variant="outlined"
            />

            <TextField
              label="URL"
              name="url"
              type="url"
              value={formData.url}
              onChange={handleChange}
              fullWidth
              required
              variant="outlined"
            />

            <Button
              type="submit"
              variant="contained"
              disabled={isFormIncomplete}
              sx={{
                mt: 2,
                width: "fit-content",
                mx: "auto",
              }}
            >
              Add Movie
            </Button>
          </Box>
        </Box>
      </Paper>
    </Container>
  );
};

export default FavoriteItemFormMUI;
