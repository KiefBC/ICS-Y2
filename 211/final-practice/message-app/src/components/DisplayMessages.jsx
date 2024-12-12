import Message from './Message';
import List from '@mui/material/List';
import { useContext } from 'react';
import messagesContext from '../messagesContext';


const DisplayMessages = ({ searchMessage }) => {

  const { messages }  = useContext(messagesContext);

  const messagesToShow = searchMessage
    ? messages.filter((message) => message.text.toLowerCase().includes(searchMessage) )
    : messages
  
  return (
    <List sx={{ ml: 1 }}>
      {messagesToShow.map(message =>
        <Message
          key={message.id}
          id={message.id}
          messageText={message.text}
        />
      )}
    </List>
  );
}

export default DisplayMessages;