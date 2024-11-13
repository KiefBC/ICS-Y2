import styled from "styled-components";
import { useState } from "react";

const FavoriteItemForm = ({ addFavoriteMovie }) => {
  const [formData, setFormData] = useState({ title: "", url: "" });

  const handleChange = (eventTarget) => {
    const { name, value } = eventTarget.target;
    setFormData((prevData) => ({
      ...prevData,
      [name]: value,
    }));
  };

  const handleSubmit = (eventTarget) => {
    eventTarget.preventDefault();
    addFavoriteMovie(formData.title, formData.url);
    setFormData({ title: "", url: "" });
  };

  // Check if either field is empty
  const isFormIncomplete = !formData.title || !formData.url;

  return (
    <form onSubmit={handleSubmit}>
      <fieldset style={{ border: "1px solid gray", padding: "10px" }}>
        <StyledLegend>Add a Movie:</StyledLegend>

        <div
          style={{
            display: "flex",
            flexDirection: "column",
            alignItems: "flex-start",
            gap: "10px",
          }}
        >
          <StyledLabel htmlFor="title">Title:</StyledLabel>
          <input
            type="text"
            name="title"
            id="title"
            value={formData.title}
            onChange={handleChange}
            style={{ width: "300px" }}
          />
          <StyledLabel htmlFor="url">Link:</StyledLabel>
          <input
            type="url"
            name="url"
            id="url"
            value={formData.url}
            onChange={handleChange}
            style={{ width: "500px" }}
          />
        </div>

        <div
          style={{
            display: "flex",
            justifyContent: "center",
            marginTop: "15px",
          }}
        >
          <StyledButton type="submit" disabled={isFormIncomplete}>
            Add Movie
          </StyledButton>
        </div>
      </fieldset>
    </form>
  );
};

const StyledLegend = styled.legend`
  font-weight: bold;
  color: navy;
  padding: 5px;
`;

const StyledLabel = styled.label`
  font-weight: bold;
  color: navy;
  padding: 5px;
`;

const StyledButton = styled.button`
  width: auto;
  padding: 10px 20px;
  background-color: #ccc;
  border: none;
  border-radius: 5px;
  cursor: pointer;
  font-size: 1rem;
  opacity: ${(props) => (props.disabled ? 0.5 : 1)};
  pointer-events: ${(props) => (props.disabled ? "none" : "auto")};

  &:hover {
    background-color: green;
  }
`;

export default FavoriteItemForm;
