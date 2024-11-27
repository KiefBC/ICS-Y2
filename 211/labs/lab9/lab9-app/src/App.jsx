import styled from "styled-components";
import Header from "./components/Header";
import { MovieProvider } from "./MovieContext";
import { ThemeProvider, createTheme } from "@mui/material";
import { BrowserRouter, Routes, Route, Link } from "react-router-dom";
import { Button, Box } from "@mui/material";
import Home from "./pages/Home";
import AddMovie from "./pages/AddMovie";

const theme = createTheme({
  palette: {
    primary: {
      main: "#1976d2",
    },
    secondary: {
      main: "#dc004e",
    },
  },
});

const App = ({ className }) => {
  return (
    <BrowserRouter>
      <ThemeProvider theme={theme}>
        <MovieProvider>
          <div className={className}>
            <StyledTitle>Favorite Movies</StyledTitle>
            <Header />

            <Box
              sx={{ mb: 4, display: "flex", gap: 2, justifyContent: "center" }}
            >
              <Button
                component={Link}
                to="/"
                variant="contained"
                color="primary"
              >
                Home
              </Button>
              <Button
                component={Link}
                to="/add"
                variant="contained"
                color="secondary"
              >
                Add Movie
              </Button>
            </Box>

            <Routes>
              <Route path="/" element={<Home />} />
              <Route path="/add" element={<AddMovie />} />
            </Routes>
          </div>
        </MovieProvider>
      </ThemeProvider>
    </BrowserRouter>
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
