import { useState } from "react";
import styled from "styled-components";

const FavoriteItemFilter = ({ onFilterChange }) => {
  const [filterText, setFilterText] = useState("");
  const [isEnabled, setIsEnabled] = useState(false);

  const handleChange = (eventTarget) => {
    const value = eventTarget.target.value;
    setFilterText(value);
    onFilterChange(isEnabled ? value : "");
  };

  const handleCheckboxChange = (eventTarget) => {
    const checked = eventTarget.target.checked;
    setIsEnabled(checked);
    onFilterChange(checked ? filterText : "");
  };

  return (
    <StyledFilterContainer $disabled={!isEnabled}>
      <StyledCheckboxContainer>
        <input
          type="checkbox"
          id="filter-enabled"
          checked={isEnabled}
          onChange={handleCheckboxChange}
        />
        <StyledCheckboxLabel htmlFor="filter-enabled">
          Enable Filter
        </StyledCheckboxLabel>
      </StyledCheckboxContainer>
      <div>
        <StyledFilterLabel>Show only movies containing:</StyledFilterLabel>
        <StyledFilterInput
          type="text"
          value={filterText}
          onChange={handleChange}
          placeholder="Type to filter..."
          disabled={!isEnabled}
        />
      </div>
    </StyledFilterContainer>
  );
};

const StyledFilterContainer = styled.div`
  margin: 20px 0;
  text-align: center;
  background-color: #d0e7ff;
  padding: 10px;
  border-radius: 5px;
  opacity: ${(props) => (props.$disabled ? 0.6 : 1)};
  transition: opacity 0.3s ease;
`;

const StyledCheckboxContainer = styled.div`
  margin-bottom: 10px;
  text-align: left;
`;

const StyledCheckboxLabel = styled.label`
  font-weight: bold;
  color: navy;
  margin-left: 5px;
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

  &:disabled {
    background-color: #f0f0f0;
    cursor: not-allowed;
  }
`;

export default FavoriteItemFilter;
