import { useState } from "react";
import {
  Box,
  Button,
  FormControl,
  TextField
} from '@mui/material';

const EnterMessageForm = ({ addMessage }) => {

  const [message, setMessage] = useState('');


  const addNewMessage = event => {
    event.preventDefault();
    addMessage(message);
    setMessage('');
  }


  return (
    <Box sx={{ height: 150, width: 365, m: 2, p: 2, border: '2px solid grey'}}>
      <form onSubmit={addNewMessage}>
        <FormControl component="fieldset"
          sx={{ display: 'flex', alignItems: 'center', flexDirection: 'column', gap: '1em' }}>
          <TextField
            label="Enter a Message:"
            value={message}
            onChange={event => setMessage(event.target.value)}
          />
          <Button
            variant="contained"
            color="primary"
            type="submit" disabled={!message}>Add Message</Button>
        </FormControl>
      </form>
    </Box>
  );
}

export default EnterMessageForm;