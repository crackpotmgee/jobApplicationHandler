grant SELECT, INSERT, UPDATE, DELETE ON token_cache to api_service;
grant SELECT, INSERT, UPDATE, DELETE ON platform_user to api_service;
grant SELECT, INSERT, UPDATE, DELETE ON platform_message to api_service;
GRANT USAGE, SELECT ON SEQUENCE platform_message_id_seq TO api_service;