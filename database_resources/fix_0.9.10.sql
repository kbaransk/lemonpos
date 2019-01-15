# Fixes to migrate from 0.9.9 to 0.9.10 database version
# (C) Krzysztof Baranski 2019 [GPL v2 or later]
#
# run this as: mysql -u root -p < fix_0.9.10.sql


use lemondb;

ALTER TABLE `transactions` ADD `paidWithPointsValue` DOUBLE UNSIGNED NOT NULL DEFAULT '0';
ALTER TABLE `transactions` ADD `paidWithPointsPoints` INT(10) NOT NULL DEFAULT '0';
