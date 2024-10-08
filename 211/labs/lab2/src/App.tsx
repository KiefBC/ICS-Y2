import './App.css'

function App() {
    return (
        <>
            <h1>ICS 211 Lab 2</h1>
            <div className="card">
                <button className={ "spacing" } onClick={() => window.location.href = "task1.html"}>
                    Go to task 2
                </button>

                <button className={ "spacing" } onClick={() => window.location.href = "task3.html"}>
                    Go to task 3
                </button>
            </div>
            <p className="read-the-docs">
                I'm more of a Svelte guy, but I'm trying to learn React. I'm not sure if I like it yet.
            </p>
        </>
    )
}

export default App
