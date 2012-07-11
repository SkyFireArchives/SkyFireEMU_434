ALTER TABLE `realmlist`
ADD COLUMN `flags` tinyint(3) UNSIGNED NOT NULL DEFAULT '0' AFTER `icon`;