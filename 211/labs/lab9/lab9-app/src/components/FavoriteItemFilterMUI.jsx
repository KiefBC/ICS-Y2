import { useState } from "react";
import { useMovies } from "../MovieContext";
import {
  Paper,
  Container,
  Box,
  TextField,
  FormControlLabel,
  Switch,
  Typography,
} from "@mui/material";

const FavoriteItemFilterMUI = () => {
  const { handleFilterChange } = useMovies();
  const [filterText, setFilterText] = useState("");
  const [isEnabled, setIsEnabled] = useState(false);

  const handleTextChange = (e) => {
    const value = e.target.value;
    setFilterText(value);
    handleFilterChange(isEnabled ? value : "");
  };

  const handleSwitchChange = (e) => {
    const checked = e.target.checked;
    setIsEnabled(checked);
    handleFilterChange(checked ? filterText : "");
  };

  return (
    <Container maxWidth="md">
      <Paper elevation={3} sx={{ p: 3, my: 2, opacity: isEnabled ? 1 : 0.8 }}>
        <Box sx={{ display: "flex", flexDirection: "column", gap: 2 }}>
          <FormControlLabel
            control={
              <Switch
                checked={isEnabled}
                onChange={handleSwitchChange}
                color="primary"
              />
            }
            label={
              <Typography color="primary" fontWeight="bold">
                Enable Filter
              </Typography>
            }
          />

          <TextField
            label="Show only movies containing"
            value={filterText}
            onChange={handleTextChange}
            disabled={!isEnabled}
            placeholder="Type to filter..."
            fullWidth
            variant="outlined"
            size="small"
          />
        </Box>
      </Paper>
    </Container>
  );
};

export default FavoriteItemFilterMUI;
