import { useState } from "react";
import styled from "styled-components";

const FavoriteItemFilter = ({ onFilterChange }) => {
  const [filterText, setFilterText] = useState("");

  const handleChange = (e) => {
    const value = e.target.value;
    setFilterText(value);
    onFilterChange(value);
  };

  return (
    <StyledFilterContainer>
      <StyledFilterLabel>Show only movies containing:</StyledFilterLabel>
      <StyledFilterInput
        type="text"
        value={filterText}
        onChange={handleChange}
        placeholder="Type to filter..."
      />
    </StyledFilterContainer>
  );
};

const StyledFilterContainer = styled.div`
  margin: 20px 0;
  text-align: center;
  background-color: #d0e7ff;
  padding: 10px;
  border-radius: 5px;
`;

const StyledFilterLabel = styled.label`
  font-weight: bold;
  color: navy;
  margin-right: 10px;
`;

const StyledFilterInput = styled.input`
  width: 60%;
  padding: 8px;
  border-radius: 4px;
  border: 1px solid #ccc;
`;

export default FavoriteItemFilter;
