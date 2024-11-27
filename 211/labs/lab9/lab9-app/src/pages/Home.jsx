import { Container, Typography } from '@mui/material';
import FavoriteItemListMUI from '../components/FavoriteItemListMUI';
import FavoriteItemFilterMUI from '../components/FavoriteItemFilterMUI';

const Home = () => {
  return (
    <Container>
      <Typography variant="h4" color="primary" gutterBottom>
        My Favorite Movies
      </Typography>
      <FavoriteItemFilterMUI />
      <FavoriteItemListMUI />
    </Container>
  );
};

export default Home; 