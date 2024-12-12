import axios from 'axios';


const getAll = () => 
  axios.get(import.meta.env.VITE_SERVICE_URL).then(response => response.data);


const create = object =>
  axios.post(import.meta.env.VITE_SERVICE_URL, object).then(response => response.data);


const update = ( id, object ) =>
  axios.patch(`${import.meta.env.VITE_SERVICE_URL}/${id}`, object).then(response => response.data);


const deleteOne = id =>
  axios.delete(`${import.meta.env.VITE_SERVICE_URL}/${id}`).then(response => response.data);


export default {
  getAll,
  create,
  update,
  deleteOne
};