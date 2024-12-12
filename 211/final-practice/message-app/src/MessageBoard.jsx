import { useState } from 'react';
import FilterMessage from "./components/FilterMessage";
import DisplayMessages from "./components/DisplayMessages";
import Box from '@mui/material/Box';
import { Link } from 'react-router';

const MessageBoard = ({changePage}) => {

  const [searchMessage, setSearchMessage] = useState('');
    
  return (
    <>
      <FilterMessage searchMessage={searchMessage}
        handleSearchMessageChange=
          {event => setSearchMessage(event.target.value)}
      />
      <Box sx={{ ml: 2, mt: 2, width: 265, display: 'flex', justifyContent: 'flex-end' }}>
        <Link
          to="/addmessage"
        >
          Add a Message
        </Link>
        {/* <Link href="#"
          onClick={changePage}>Add a Message 
        </Link> */}
      </Box>
      <DisplayMessages
        searchMessage={searchMessage}
      />
    </>
  );
}

export default MessageBoard;