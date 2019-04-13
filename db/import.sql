-- MySQL dump 10.16  Distrib 10.1.9-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: z
-- ------------------------------------------------------
-- Server version	10.1.9-MariaDB-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Dumping data for table `achievementconditions`
--

LOCK TABLES `achievementconditions` WRITE;
/*!40000 ALTER TABLE `achievementconditions` DISABLE KEYS */;
INSERT INTO `achievementconditions` (`id`, `created`, `condition`) VALUES (1,'2014-04-16 19:36:54','date'),(2,'2014-04-16 19:36:54','character'),(3,'2014-04-16 19:36:59','quest'),(4,'2014-04-16 19:36:59','achievement'),(5,'2016-03-06 11:47:50','qrcode');
/*!40000 ALTER TABLE `achievementconditions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `achievementconditions_achievement`
--

LOCK TABLES `achievementconditions_achievement` WRITE;
/*!40000 ALTER TABLE `achievementconditions_achievement` DISABLE KEYS */;
/*!40000 ALTER TABLE `achievementconditions_achievement` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `achievementconditions_character`
--

LOCK TABLES `achievementconditions_character` WRITE;
/*!40000 ALTER TABLE `achievementconditions_character` DISABLE KEYS */;
/*!40000 ALTER TABLE `achievementconditions_character` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `achievementconditions_date`
--

LOCK TABLES `achievementconditions_date` WRITE;
/*!40000 ALTER TABLE `achievementconditions_date` DISABLE KEYS */;
/*!40000 ALTER TABLE `achievementconditions_date` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `achievementconditions_quest`
--

LOCK TABLES `achievementconditions_quest` WRITE;
/*!40000 ALTER TABLE `achievementconditions_quest` DISABLE KEYS */;
/*!40000 ALTER TABLE `achievementconditions_quest` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `achievements`
--

LOCK TABLES `achievements` WRITE;
/*!40000 ALTER TABLE `achievements` DISABLE KEYS */;
/*!40000 ALTER TABLE `achievements` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `achievements_characters`
--

LOCK TABLES `achievements_characters` WRITE;
/*!40000 ALTER TABLE `achievements_characters` DISABLE KEYS */;
/*!40000 ALTER TABLE `achievements_characters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `achievementsmedia`
--

LOCK TABLES `achievementsmedia` WRITE;
/*!40000 ALTER TABLE `achievementsmedia` DISABLE KEYS */;
/*!40000 ALTER TABLE `achievementsmedia` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `avatarpictures`
--

LOCK TABLES `avatarpictures` WRITE;
/*!40000 ALTER TABLE `avatarpictures` DISABLE KEYS */;
/*!40000 ALTER TABLE `avatarpictures` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `avatars`
--

LOCK TABLES `avatars` WRITE;
/*!40000 ALTER TABLE `avatars` DISABLE KEYS */;
/*!40000 ALTER TABLE `avatars` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `cache_charactergroups`
--

LOCK TABLES `cache_charactergroups` WRITE;
/*!40000 ALTER TABLE `cache_charactergroups` DISABLE KEYS */;
/*!40000 ALTER TABLE `cache_charactergroups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `cache_characters`
--

LOCK TABLES `cache_characters` WRITE;
/*!40000 ALTER TABLE `cache_characters` DISABLE KEYS */;
/*!40000 ALTER TABLE `cache_characters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `charactergroups`
--

LOCK TABLES `charactergroups` WRITE;
/*!40000 ALTER TABLE `charactergroups` DISABLE KEYS */;
/*!40000 ALTER TABLE `charactergroups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `charactergroupsgroups`
--

LOCK TABLES `charactergroupsgroups` WRITE;
/*!40000 ALTER TABLE `charactergroupsgroups` DISABLE KEYS */;
/*!40000 ALTER TABLE `charactergroupsgroups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `charactergroupsmedia`
--

LOCK TABLES `charactergroupsmedia` WRITE;
/*!40000 ALTER TABLE `charactergroupsmedia` DISABLE KEYS */;
/*!40000 ALTER TABLE `charactergroupsmedia` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `charactergroupsquests`
--

LOCK TABLES `charactergroupsquests` WRITE;
/*!40000 ALTER TABLE `charactergroupsquests` DISABLE KEYS */;
/*!40000 ALTER TABLE `charactergroupsquests` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `charactergroupsquests_groups`
--

LOCK TABLES `charactergroupsquests_groups` WRITE;
/*!40000 ALTER TABLE `charactergroupsquests_groups` DISABLE KEYS */;
/*!40000 ALTER TABLE `charactergroupsquests_groups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `charactergroupsquests_seminaryuploads`
--

LOCK TABLES `charactergroupsquests_seminaryuploads` WRITE;
/*!40000 ALTER TABLE `charactergroupsquests_seminaryuploads` DISABLE KEYS */;
/*!40000 ALTER TABLE `charactergroupsquests_seminaryuploads` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `charactergroupsqueststations`
--

LOCK TABLES `charactergroupsqueststations` WRITE;
/*!40000 ALTER TABLE `charactergroupsqueststations` DISABLE KEYS */;
/*!40000 ALTER TABLE `charactergroupsqueststations` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `charactergroupsqueststations_charactergroups`
--

LOCK TABLES `charactergroupsqueststations_charactergroups` WRITE;
/*!40000 ALTER TABLE `charactergroupsqueststations_charactergroups` DISABLE KEYS */;
/*!40000 ALTER TABLE `charactergroupsqueststations_charactergroups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `characterroles`
--

LOCK TABLES `characterroles` WRITE;
/*!40000 ALTER TABLE `characterroles` DISABLE KEYS */;
INSERT INTO `characterroles` (`id`, `created`, `name`) VALUES (1,'2014-04-16 14:42:54','admin'),(2,'2014-04-16 14:42:54','moderator'),(3,'2014-04-16 14:43:00','user'),(4,'2014-04-16 14:43:00','guest');
/*!40000 ALTER TABLE `characterroles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `characters`
--

LOCK TABLES `characters` WRITE;
/*!40000 ALTER TABLE `characters` DISABLE KEYS */;
/*!40000 ALTER TABLE `characters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `characters_charactergroups`
--

LOCK TABLES `characters_charactergroups` WRITE;
/*!40000 ALTER TABLE `characters_charactergroups` DISABLE KEYS */;
/*!40000 ALTER TABLE `characters_charactergroups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `characters_characterroles`
--

LOCK TABLES `characters_characterroles` WRITE;
/*!40000 ALTER TABLE `characters_characterroles` DISABLE KEYS */;
/*!40000 ALTER TABLE `characters_characterroles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `characters_seminarycharacterfields`
--

LOCK TABLES `characters_seminarycharacterfields` WRITE;
/*!40000 ALTER TABLE `characters_seminarycharacterfields` DISABLE KEYS */;
/*!40000 ALTER TABLE `characters_seminarycharacterfields` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `charactertypes`
--

LOCK TABLES `charactertypes` WRITE;
/*!40000 ALTER TABLE `charactertypes` DISABLE KEYS */;
/*!40000 ALTER TABLE `charactertypes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `maps`
--

LOCK TABLES `maps` WRITE;
/*!40000 ALTER TABLE `maps` DISABLE KEYS */;
/*!40000 ALTER TABLE `maps` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `media`
--

LOCK TABLES `media` WRITE;
/*!40000 ALTER TABLE `media` DISABLE KEYS */;
/*!40000 ALTER TABLE `media` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `pages`
--

LOCK TABLES `pages` WRITE;
/*!40000 ALTER TABLE `pages` DISABLE KEYS */;
/*!40000 ALTER TABLE `pages` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questgroups`
--

LOCK TABLES `questgroups` WRITE;
/*!40000 ALTER TABLE `questgroups` DISABLE KEYS */;
/*!40000 ALTER TABLE `questgroups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questgroups_characters`
--

LOCK TABLES `questgroups_characters` WRITE;
/*!40000 ALTER TABLE `questgroups_characters` DISABLE KEYS */;
/*!40000 ALTER TABLE `questgroups_characters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questgroups_questgroupshierarchy`
--

LOCK TABLES `questgroups_questgroupshierarchy` WRITE;
/*!40000 ALTER TABLE `questgroups_questgroupshierarchy` DISABLE KEYS */;
/*!40000 ALTER TABLE `questgroups_questgroupshierarchy` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questgroups_questtexts`
--

LOCK TABLES `questgroups_questtexts` WRITE;
/*!40000 ALTER TABLE `questgroups_questtexts` DISABLE KEYS */;
/*!40000 ALTER TABLE `questgroups_questtexts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questgroupshierarchy`
--

LOCK TABLES `questgroupshierarchy` WRITE;
/*!40000 ALTER TABLE `questgroupshierarchy` DISABLE KEYS */;
/*!40000 ALTER TABLE `questgroupshierarchy` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questgroupspictures`
--

LOCK TABLES `questgroupspictures` WRITE;
/*!40000 ALTER TABLE `questgroupspictures` DISABLE KEYS */;
/*!40000 ALTER TABLE `questgroupspictures` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questgrouptexts`
--

LOCK TABLES `questgrouptexts` WRITE;
/*!40000 ALTER TABLE `questgrouptexts` DISABLE KEYS */;
/*!40000 ALTER TABLE `questgrouptexts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `quests`
--

LOCK TABLES `quests` WRITE;
/*!40000 ALTER TABLE `quests` DISABLE KEYS */;
/*!40000 ALTER TABLE `quests` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `quests_characters`
--

LOCK TABLES `quests_characters` WRITE;
/*!40000 ALTER TABLE `quests_characters` DISABLE KEYS */;
/*!40000 ALTER TABLE `quests_characters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `quests_previousquests`
--

LOCK TABLES `quests_previousquests` WRITE;
/*!40000 ALTER TABLE `quests_previousquests` DISABLE KEYS */;
/*!40000 ALTER TABLE `quests_previousquests` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `quests_questsubtopics`
--

LOCK TABLES `quests_questsubtopics` WRITE;
/*!40000 ALTER TABLE `quests_questsubtopics` DISABLE KEYS */;
/*!40000 ALTER TABLE `quests_questsubtopics` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questsmedia`
--

LOCK TABLES `questsmedia` WRITE;
/*!40000 ALTER TABLE `questsmedia` DISABLE KEYS */;
/*!40000 ALTER TABLE `questsmedia` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questsubtopics`
--

LOCK TABLES `questsubtopics` WRITE;
/*!40000 ALTER TABLE `questsubtopics` DISABLE KEYS */;
/*!40000 ALTER TABLE `questsubtopics` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtexts`
--

LOCK TABLES `questtexts` WRITE;
/*!40000 ALTER TABLE `questtexts` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtexts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtexttypes`
--

LOCK TABLES `questtexttypes` WRITE;
/*!40000 ALTER TABLE `questtexttypes` DISABLE KEYS */;
INSERT INTO `questtexttypes` (`id`, `created`, `type`, `url`) VALUES (1,'2014-04-17 09:24:21','Prolog','Prolog'),(2,'2014-04-17 09:24:21','Hint','Hint'),(3,'2014-04-17 09:24:27','Epilog','Epilog');
/*!40000 ALTER TABLE `questtexttypes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtopics`
--

LOCK TABLES `questtopics` WRITE;
/*!40000 ALTER TABLE `questtopics` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtopics` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes`
--

LOCK TABLES `questtypes` WRITE;
/*!40000 ALTER TABLE `questtypes` DISABLE KEYS */;
INSERT INTO `questtypes` (`id`, `created`, `title`, `url`, `classname`) VALUES (1,'2014-04-16 18:44:44','Empty','Empty',NULL),(2,'2014-04-16 18:44:44','Boss Fight','Boss-Fight','bossfight'),(3,'2014-04-16 18:45:19','Choice Input','Choice-Input','choiceinput'),(4,'2014-04-16 18:46:02','Crossword','Crossword','crossword'),(5,'2014-04-16 18:46:02','Drag&Drop','Drag&Drop','dragndrop'),(6,'2014-04-16 18:46:23','Multiple Choice','Multiple-Choice','multiplechoice'),(7,'2014-04-16 18:46:23','Submit','Submit','submit'),(8,'2014-04-16 18:46:43','Text Input','Text-Input','textinput');
/*!40000 ALTER TABLE `questtypes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_bossfight`
--

LOCK TABLES `questtypes_bossfight` WRITE;
/*!40000 ALTER TABLE `questtypes_bossfight` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_bossfight` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_bossfight_stages`
--

LOCK TABLES `questtypes_bossfight_stages` WRITE;
/*!40000 ALTER TABLE `questtypes_bossfight_stages` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_bossfight_stages` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_bossfight_stages_characters`
--

LOCK TABLES `questtypes_bossfight_stages_characters` WRITE;
/*!40000 ALTER TABLE `questtypes_bossfight_stages_characters` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_bossfight_stages_characters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_choiceinput`
--

LOCK TABLES `questtypes_choiceinput` WRITE;
/*!40000 ALTER TABLE `questtypes_choiceinput` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_choiceinput` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_choiceinput_choices`
--

LOCK TABLES `questtypes_choiceinput_choices` WRITE;
/*!40000 ALTER TABLE `questtypes_choiceinput_choices` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_choiceinput_choices` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_choiceinput_lists`
--

LOCK TABLES `questtypes_choiceinput_lists` WRITE;
/*!40000 ALTER TABLE `questtypes_choiceinput_lists` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_choiceinput_lists` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_choiceinput_lists_characters`
--

LOCK TABLES `questtypes_choiceinput_lists_characters` WRITE;
/*!40000 ALTER TABLE `questtypes_choiceinput_lists_characters` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_choiceinput_lists_characters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_crossword_words`
--

LOCK TABLES `questtypes_crossword_words` WRITE;
/*!40000 ALTER TABLE `questtypes_crossword_words` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_crossword_words` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_crossword_words_characters`
--

LOCK TABLES `questtypes_crossword_words_characters` WRITE;
/*!40000 ALTER TABLE `questtypes_crossword_words_characters` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_crossword_words_characters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_dragndrop`
--

LOCK TABLES `questtypes_dragndrop` WRITE;
/*!40000 ALTER TABLE `questtypes_dragndrop` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_dragndrop` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_dragndrop_drags`
--

LOCK TABLES `questtypes_dragndrop_drags` WRITE;
/*!40000 ALTER TABLE `questtypes_dragndrop_drags` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_dragndrop_drags` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_dragndrop_drops`
--

LOCK TABLES `questtypes_dragndrop_drops` WRITE;
/*!40000 ALTER TABLE `questtypes_dragndrop_drops` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_dragndrop_drops` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_dragndrop_drops_characters`
--

LOCK TABLES `questtypes_dragndrop_drops_characters` WRITE;
/*!40000 ALTER TABLE `questtypes_dragndrop_drops_characters` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_dragndrop_drops_characters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_dragndrop_drops_drags`
--

LOCK TABLES `questtypes_dragndrop_drops_drags` WRITE;
/*!40000 ALTER TABLE `questtypes_dragndrop_drops_drags` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_dragndrop_drops_drags` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_multiplechoice`
--

LOCK TABLES `questtypes_multiplechoice` WRITE;
/*!40000 ALTER TABLE `questtypes_multiplechoice` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_multiplechoice` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_multiplechoice_answers`
--

LOCK TABLES `questtypes_multiplechoice_answers` WRITE;
/*!40000 ALTER TABLE `questtypes_multiplechoice_answers` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_multiplechoice_answers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_multiplechoice_characters`
--

LOCK TABLES `questtypes_multiplechoice_characters` WRITE;
/*!40000 ALTER TABLE `questtypes_multiplechoice_characters` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_multiplechoice_characters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_submit_characters`
--

LOCK TABLES `questtypes_submit_characters` WRITE;
/*!40000 ALTER TABLE `questtypes_submit_characters` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_submit_characters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_submit_characters_comments`
--

LOCK TABLES `questtypes_submit_characters_comments` WRITE;
/*!40000 ALTER TABLE `questtypes_submit_characters_comments` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_submit_characters_comments` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_textinput`
--

LOCK TABLES `questtypes_textinput` WRITE;
/*!40000 ALTER TABLE `questtypes_textinput` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_textinput` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_textinput_fields`
--

LOCK TABLES `questtypes_textinput_fields` WRITE;
/*!40000 ALTER TABLE `questtypes_textinput_fields` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_textinput_fields` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_textinput_fields_characters`
--

LOCK TABLES `questtypes_textinput_fields_characters` WRITE;
/*!40000 ALTER TABLE `questtypes_textinput_fields_characters` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_textinput_fields_characters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `questtypes_textinput_fieldsizes`
--

LOCK TABLES `questtypes_textinput_fieldsizes` WRITE;
/*!40000 ALTER TABLE `questtypes_textinput_fieldsizes` DISABLE KEYS */;
/*!40000 ALTER TABLE `questtypes_textinput_fieldsizes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `seminaries`
--

LOCK TABLES `seminaries` WRITE;
/*!40000 ALTER TABLE `seminaries` DISABLE KEYS */;
/*!40000 ALTER TABLE `seminaries` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `seminarycharacterfields`
--

LOCK TABLES `seminarycharacterfields` WRITE;
/*!40000 ALTER TABLE `seminarycharacterfields` DISABLE KEYS */;
/*!40000 ALTER TABLE `seminarycharacterfields` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `seminarycharacterfieldtypes`
--

LOCK TABLES `seminarycharacterfieldtypes` WRITE;
/*!40000 ALTER TABLE `seminarycharacterfieldtypes` DISABLE KEYS */;
INSERT INTO `seminarycharacterfieldtypes` (`id`, `created`, `title`, `url`) VALUES (1,'2014-04-16 18:50:16','Number','Number'),(2,'2014-04-16 18:50:16','Varchar','Varchar'),(3,'2014-04-16 18:50:24','Text','Text'),(4,'2014-04-16 18:50:24','List','List');
/*!40000 ALTER TABLE `seminarycharacterfieldtypes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `seminarymedia`
--

LOCK TABLES `seminarymedia` WRITE;
/*!40000 ALTER TABLE `seminarymedia` DISABLE KEYS */;
/*!40000 ALTER TABLE `seminarymedia` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `seminaryuploads`
--

LOCK TABLES `seminaryuploads` WRITE;
/*!40000 ALTER TABLE `seminaryuploads` DISABLE KEYS */;
/*!40000 ALTER TABLE `seminaryuploads` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `stationtypes`
--

LOCK TABLES `stationtypes` WRITE;
/*!40000 ALTER TABLE `stationtypes` DISABLE KEYS */;
INSERT INTO `stationtypes` (`id`, `created`, `title`, `url`, `classname`) VALUES (1,'2015-12-25 15:50:52','Empty','Empty',NULL),(2,'2015-12-25 15:50:52','Keyword','Keyword','keyword'),(3,'2015-12-25 15:51:16','Multiple Choice','Multiple-Choice','multiplechoice'),(4,'2016-02-27 17:22:11','Single Choice','Single-Choice','singlechoice');
/*!40000 ALTER TABLE `stationtypes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `stationtypes_keyword`
--

LOCK TABLES `stationtypes_keyword` WRITE;
/*!40000 ALTER TABLE `stationtypes_keyword` DISABLE KEYS */;
/*!40000 ALTER TABLE `stationtypes_keyword` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `stationtypes_keyword_charactergroups`
--

LOCK TABLES `stationtypes_keyword_charactergroups` WRITE;
/*!40000 ALTER TABLE `stationtypes_keyword_charactergroups` DISABLE KEYS */;
/*!40000 ALTER TABLE `stationtypes_keyword_charactergroups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `stationtypes_multiplechoice`
--

LOCK TABLES `stationtypes_multiplechoice` WRITE;
/*!40000 ALTER TABLE `stationtypes_multiplechoice` DISABLE KEYS */;
/*!40000 ALTER TABLE `stationtypes_multiplechoice` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `stationtypes_multiplechoice_charactergroups`
--

LOCK TABLES `stationtypes_multiplechoice_charactergroups` WRITE;
/*!40000 ALTER TABLE `stationtypes_multiplechoice_charactergroups` DISABLE KEYS */;
/*!40000 ALTER TABLE `stationtypes_multiplechoice_charactergroups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `userroles`
--

LOCK TABLES `userroles` WRITE;
/*!40000 ALTER TABLE `userroles` DISABLE KEYS */;
INSERT INTO `userroles` (`id`, `created`, `name`) VALUES (1,'2014-04-16 14:42:54','admin'),(2,'2014-04-16 14:42:54','moderator'),(3,'2014-04-16 14:43:00','user'),(4,'2014-04-16 14:43:00','guest');
/*!40000 ALTER TABLE `userroles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` (`id`, `created`, `username`, `url`, `surname`, `prename`, `email`, `password`, `mailing`) VALUES (1,'2015-04-26 11:24:04','admin','admin','Admin','Admin','','$2y$10$1zCozXcIGak552mkv/K3vOPddrisvPlokJvUjHtHj6VBBRcmznXCG',1);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `users_userroles`
--

LOCK TABLES `users_userroles` WRITE;
/*!40000 ALTER TABLE `users_userroles` DISABLE KEYS */;
INSERT INTO `users_userroles` (`user_id`, `userrole_id`, `created`) VALUES (1,1,'2015-04-26 11:33:36');
/*!40000 ALTER TABLE `users_userroles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `xplevels`
--

LOCK TABLES `xplevels` WRITE;
/*!40000 ALTER TABLE `xplevels` DISABLE KEYS */;
/*!40000 ALTER TABLE `xplevels` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-12-25 16:51:58
