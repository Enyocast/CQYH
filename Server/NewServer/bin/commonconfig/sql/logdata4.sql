DROP PROCEDURE IF EXISTS `check_version`;
DROP PROCEDURE IF EXISTS `update_db`;

CREATE PROCEDURE check_version(OUT ret INT)
BEGIN
	DECLARE ver INT;
	SET ret = 0;
	SELECT number INTO ver FROM `version` WHERE id = 'all';
	IF ver = 3 THEN
		SET ret = 1;
	END IF;
END;

CREATE PROCEDURE update_db()
BEGIN
	DECLARE ret INT;
	CALL check_version(ret);
	IF ret = 1 THEN
		ALTER TABLE logdata_accountlogin ENGINE=InnoDB;
		ALTER TABLE logdata_gm ENGINE=InnoDB;
		ALTER TABLE logdata_item ENGINE=InnoDB;
		ALTER TABLE logdata_money ENGINE=InnoDB;
		ALTER TABLE logdata_quest ENGINE=InnoDB;
		ALTER TABLE logdata_rolelogout_basic ENGINE=InnoDB;
		ALTER TABLE logdata_servermonitor_consecutivekillnpc ENGINE=InnoDB;
		ALTER TABLE logdata_servermonitor_momentarykillnpc ENGINE=InnoDB;
		ALTER TABLE logdata_servermonitor_money ENGINE=InnoDB;
		ALTER TABLE logdata_servermonitor_npcdie ENGINE=InnoDB;
		ALTER TABLE logdata_servermonitor_questcomplete ENGINE=InnoDB;
		ALTER TABLE logdata_servermonitor_realmoney ENGINE=InnoDB;
		ALTER TABLE version ENGINE=InnoDB;

		UPDATE version SET number = 4 where id = 'all';
	END IF;
END;

CALL update_db();

DROP PROCEDURE IF EXISTS `check_version`;
DROP PROCEDURE IF EXISTS `update_db`;
