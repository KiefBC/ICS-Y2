    const favoriteMovies = [
      {
        id: 0,
        title: "The Dark Knight",
        genre: "Action",
        url: "https://www.imdb.com/title/tt0468569/"
      },
      {
        id: 1,
        title: "The Godfather",
        genre: "Crime",
        url: "https://www.imdb.com/title/tt0068646/"
      },
      {
        id: 2,
        title: "The Lord of the Rings: The Return of the King",
        genre: "Action",
        url: "https://www.imdb.com/title/tt0167261/"
      },
    ];

    const Header = () => {
      return (
        <>
          <div id={"header"}>
            <div id={"header-title"}>
              <h1>ICS 211 - Lab 3!</h1>
            </div>
            <div id={"header-subtitle"}>
              <h3>Made by Kiefer with React</h3>
            </div>
          </div>
        </>
      )
    };

    const FavoriteMovie = ({title, genre, url}) => {
      return (
        <li>
          {title} ({genre}): <a href={url}>{url}</a>
        </li>
      )
    }

    const FavoriteMovieList = ({favoriteMovies}) => {
      return (
        <div id={"favorite-movies"}>
          <ol>
            {favoriteMovies.map(movie => (
              <FavoriteMovie key={movie.id} {...movie} />
            ))}
          </ol>
        </div>
      )
    }

    const App = () => {
      return (
        <>
          <Header />
          <FavoriteMovieList favoriteMovies={favoriteMovies} />
        </>
      );
    }
