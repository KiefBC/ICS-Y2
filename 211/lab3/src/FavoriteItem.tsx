import { StrictMode } from 'react';
import { createRoot } from 'react-dom/client';
import './App.css';
import './index.css';

// Define a type for movie details
interface Movie {
    title: string;
    imdbLink: string;
}

const favoriteMovies: Movie[] = [
    { title: "The Dark Knight", imdbLink: "https://www.imdb.com/title/tt0468569/" },
    { title: "The Matrix", imdbLink: "https://www.imdb.com/title/tt0133093/" },
    { title: "Pulp Fiction", imdbLink: "https://www.imdb.com/title/tt0110912/" },
];

function MovieList() {
    return (
        <div>
            <h1>Favorite Movies</h1>
            <h3>By Kiefer Hay</h3>
            <ol>
                {favoriteMovies.map((movie, index) => (
                    <li key={index}>
                        {movie.title}:{" "}
                        <a href={movie.imdbLink} target="_blank" rel="noopener noreferrer">
                            {movie.imdbLink}
                        </a>
                    </li>
                ))}
            </ol>

            <div className="card">
                <button className="spacing" onClick={() => window.location.href = "index.html"}>
                    Go to Home
                </button>

                <button className="spacing" onClick={() => window.location.href = "task1.html"}>
                    Go to task 2
                </button>
            </div>
        </div>
    );
}

createRoot(document.getElementById('root')!).render(
    <StrictMode>
        <MovieList />
    </StrictMode>,
);
