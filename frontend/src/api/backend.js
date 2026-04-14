import axios from "axios";

// Vite exposes any VITE_-prefixed env var to the client bundle.
// Set VITE_API_BASE in Vercel (and optionally in frontend/.env.local for dev)
// to point at the deployed Flask backend.
const baseURL = import.meta.env.VITE_API_BASE || "http://localhost:5000";

const API = axios.create({ baseURL });

export default API;
