import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import StyledApp from "./App.jsx";

createRoot(document.getElementById("root")).render(
  <StrictMode>
    <StyledApp />
  </StrictMode>,
);
