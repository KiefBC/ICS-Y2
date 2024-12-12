import { useEffect, useState } from 'react';
import EnterMessageForm from './components/EnterMessageForm';
import messageService from './services/messageService';
import messagesContext from './messagesContext';
import MessageBoard from './MessageBoard';
import { Routes, Route, useNavigate } from 'react-router';


const App = () => {
  // list of messages 
  const [messages, setMessages] = useState([]);
  //const [ showForm, setShowForm ] = useState(false);
  const navigate = useNavigate();

  //const changePage = () => setShowForm(!showForm);

  //const id = useRef(0);
  useEffect(() => {
    console.log('useEffect was executed!');
    // start of IIFE
    (async () => {
      try {
        const serverMessages = await messageService.getAll();
        setMessages(serverMessages);
      } catch (error) {
        console.log('API Error: ' + error);
      }
    })();
    // end IFFE
  },[]);

  // this will be called by addNewMessage in the Form
  // inverse data flow - pass data up to App
  const addMessage = async newMessageText => {
    
    if (messages.some( message =>
      message.text.toLowerCase() === newMessageText.toLowerCase() )) {
      alert(`${newMessageText} message is already in list of messages!`);
    } else {
      // create Message object with id and text properties
      // const newMessageObject = {
      //   id: id.current,
      //   text: newMessageText
      // }

      // POST Request
      try {
        const newMessageObject =
          await messageService.create({ text: newMessageText });
        setMessages(messages.concat(newMessageObject));
        //changePage();
        navigate('/');
      } catch (error) {
        console.log('API Error: ' + error);
      }

      // create new array and add message at end
      //setMessages(messages.concat(newMessageObject));
      //id.current += 1;
    }
  }

  const editMessage = async (modifiedMessageId, modifiedMessageText) => {
    const newMessages = messages.map( message =>
      message.id === modifiedMessageId
        ? { ...message, text: modifiedMessageText }
        : message
    );

    try {
      await messageService.update(modifiedMessageId,
        { text: modifiedMessageText });
      setMessages(newMessages);
    } catch (error) {
      console.log('API Error: ' + error);
    }
  }


  const deleteMessage = async messageId => {
    try {
      await messageService.deleteOne(messageId);
      setMessages(messages.filter( message => message.id !== messageId ));
    } catch (error) {
      console.log('API Error: ' + error);
    }
  }


  return (
    <messagesContext.Provider value={{ messages, editMessage, deleteMessage }}>
      {/* { showForm
        ? <EnterMessageForm addMessage={addMessage} />
        : <MessageBoard changePage={changePage} />
      } */}
      <Routes>
        <Route path="/" element={<MessageBoard />} />
        <Route path="/addmessage" element=
          {<EnterMessageForm addMessage={addMessage} />} />
      </Routes>
    </messagesContext.Provider>
  );
}

export default App;
