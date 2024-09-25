import React from 'react';

// Define the types of props the component will accept
interface MyComponentProps {
    title: string; // Define the props type here
}

// This tells TypeScript that MyComponent is a functional component that takes MyComponentProps as its props
const MyComponent: React.FC<MyComponentProps> = ({ title }) => {
    return (
        <div>
            <h1>{title}</h1>
            <p>This is a TypeScript React component!</p>
        </div>
    );
};

export default MyComponent;
