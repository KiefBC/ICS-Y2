import { Container, Box } from "@mui/material";
import FavoriteItemFormMUI from "./FavoriteItemFormMUI";
import FavoriteItemListMUI from "./FavoriteItemListMUI";
import FavoriteItemFilterMUI from "./FavoriteItemFilterMUI";

const FavoriteMoviesContainerMUI = () => {
  return (
    <Container maxWidth="md">
      <Box sx={{ my: 4 }}>
        <FavoriteItemFormMUI />
        <FavoriteItemFilterMUI />
        <FavoriteItemListMUI />
      </Box>
    </Container>
  );
};

export default FavoriteMoviesContainerMUI;
