REVOKE ALL PRIVILEGES ON * . * FROM 'panda'@'localhost';

REVOKE ALL PRIVILEGES ON `world` . * FROM 'panda'@'localhost';

REVOKE GRANT OPTION ON `world` . * FROM 'panda'@'localhost';

REVOKE ALL PRIVILEGES ON `characters` . * FROM 'panda'@'localhost';

REVOKE GRANT OPTION ON `characters` . * FROM 'panda'@'localhost';

REVOKE ALL PRIVILEGES ON `auth` . * FROM 'panda'@'localhost';

REVOKE GRANT OPTION ON `auth` . * FROM 'panda'@'localhost';

DROP USER 'panda'@'localhost';

DROP DATABASE IF EXISTS `world`;

DROP DATABASE IF EXISTS `characters`;

DROP DATABASE IF EXISTS `auth`;
