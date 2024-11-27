import { Container, Typography } from '@mui/material';
import FavoriteItemFormMUI from '../components/FavoriteItemFormMUI';

const AddMovie = () => {
  return (
    <Container>
      <Typography variant="h4" color="primary" gutterBottom>
        Add New Movie
      </Typography>
      <FavoriteItemFormMUI />
    </Container>
  );
};

export default AddMovie; 