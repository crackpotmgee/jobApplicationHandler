CREATE TABLE platform_user (
  id SERIAL PRIMARY KEY,
  google_sub VARCHAR(500) UNIQUE NOT NULL, 
  email VARCHAR(255) UNIQUE,
  name varchar(200),
  picture TEXT,
  created_at TIMESTAMP WITH TIME ZONE DEFAULT now(),
  last_login TIMESTAMP WITH TIME ZONE
);