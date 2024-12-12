import { useState } from 'react';

const EditMessageForm = ({ messageText, modifyMessage }) => {

  const [ modifiedText, setModifiedText] = useState(messageText);
  
  const handleFormSubmit = event => {
    event.preventDefault();
    modifyMessage(modifiedText);
  }

  return (
    <form onSubmit={handleFormSubmit}>
        <input type='text'
          value={modifiedText}
          onChange={event => setModifiedText(event.target.value)}
        />
    </form>
  );
}

export default EditMessageForm;