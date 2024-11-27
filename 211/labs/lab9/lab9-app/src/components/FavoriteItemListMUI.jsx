import { useMovies } from "../MovieContext";
import { List, Paper, Container, CircularProgress, Box } from "@mui/material";
import FavoriteItemMUI from "./FavoriteItemMUI";

const FavoriteItemListMUI = () => {
  const { favoriteMovies, filterText, handleTitleChange, handleDelete } =
    useMovies();

  if (!favoriteMovies) {
    return (
      <Box display="flex" justifyContent="center" my={4}>
        <CircularProgress />
      </Box>
    );
  }

  const filteredMovies =
    filterText === ""
      ? favoriteMovies
      : favoriteMovies.filter((movie) =>
          movie.title.toLowerCase().includes(filterText.toLowerCase()),
        );

  return (
    <Container maxWidth="md">
      <Paper elevation={3} sx={{ my: 2 }}>
        <List
          sx={{
            display: "flex",
            flexDirection: "column",
            alignItems: "center",
            py: 2,
          }}
        >
          {filteredMovies.map((movie) => (
            <FavoriteItemMUI
              key={movie.id}
              {...movie}
              onTitleChange={handleTitleChange}
              onDelete={handleDelete}
            />
          ))}
        </List>
      </Paper>
    </Container>
  );
};

export default FavoriteItemListMUI;
