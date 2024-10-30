import { useState } from 'react';
import EditMessageForm from './EditMessageForm';

    const Message = ({ id, messageText, editMessage }) => {

      const [ isEditable, setIsEditable ] = useState(false);
      
      const modifyMessage = modifiedText => {
        editMessage(id, modifiedText);
        setIsEditable(false);
      }

      return (
        <li onDoubleClick={ () => setIsEditable(true) }>
          { isEditable
            ? <EditMessageForm
                messageText={messageText}
                modifyMessage={modifyMessage}
              />
            : messageText 
          }
        </li>
      );
    };
