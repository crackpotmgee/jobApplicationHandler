CREATE TABLE users (
  id SERIAL PRIMARY KEY,
  google_sub TEXT UNIQUE NOT NULL,    -- the 'sub' from id_token (stable identifier)
  email TEXT UNIQUE,
  name TEXT,
  picture TEXT,
  created_at TIMESTAMP WITH TIME ZONE DEFAULT now(),
  last_login TIMESTAMP WITH TIME ZONE
);