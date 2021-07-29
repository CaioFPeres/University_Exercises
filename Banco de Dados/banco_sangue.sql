-- MySQL dump 10.13  Distrib 8.0.12, for Win64 (x86_64)
--
-- Host: localhost    Database: banco_sangue
-- ------------------------------------------------------
-- Server version	8.0.12

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
 SET NAMES utf8 ;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `doacoes`
--

DROP TABLE IF EXISTS `doacoes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `doacoes` (
  `IDDoacao` bigint(255) NOT NULL,
  `IDDoador` bigint(255) NOT NULL,
  `SegurancaDoacao` int(255) DEFAULT NULL,
  `DataDoacao` datetime(6) DEFAULT NULL,
  PRIMARY KEY (`IDDoacao`) USING BTREE,
  KEY `FK2` (`IDDoador`),
  KEY `FK3` (`SegurancaDoacao`),
  CONSTRAINT `FK1` FOREIGN KEY (`IDDoador`) REFERENCES `doadores` (`iddoador`),
  CONSTRAINT `FK3` FOREIGN KEY (`SegurancaDoacao`) REFERENCES `triagem` (`segurancadoacao`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `doacoes`
--

LOCK TABLES `doacoes` WRITE;
/*!40000 ALTER TABLE `doacoes` DISABLE KEYS */;
/*!40000 ALTER TABLE `doacoes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `doadores`
--

DROP TABLE IF EXISTS `doadores`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `doadores` (
  `IDDoador` bigint(255) NOT NULL,
  `RG` varchar(255) DEFAULT NULL,
  `Nome` varchar(255) DEFAULT NULL,
  `Genero` varchar(255) DEFAULT NULL,
  `Data de Nascimento` datetime(6) DEFAULT NULL,
  `Cidade` varchar(255) DEFAULT NULL,
  `Bairro` varchar(255) DEFAULT NULL,
  `Numero` varchar(255) DEFAULT NULL,
  `Pai` varchar(255) DEFAULT NULL,
  `Mae` varchar(255) DEFAULT NULL,
  `IDTIPO` int(255) DEFAULT NULL,
  PRIMARY KEY (`IDDoador`),
  KEY `IDDoador` (`IDDoador`),
  KEY `FKTIPO` (`IDTIPO`),
  KEY `IDDoador_2` (`IDDoador`),
  KEY `IDDoador_3` (`IDDoador`),
  CONSTRAINT `FKTIPO` FOREIGN KEY (`IDTIPO`) REFERENCES `tipos sanguineos` (`idtipo`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `doadores`
--

LOCK TABLES `doadores` WRITE;
/*!40000 ALTER TABLE `doadores` DISABLE KEYS */;
/*!40000 ALTER TABLE `doadores` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `exames`
--

DROP TABLE IF EXISTS `exames`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `exames` (
  `IDExame` bigint(255) NOT NULL,
  `IDDoador` bigint(255) DEFAULT NULL,
  `Hepatite B` int(255) DEFAULT NULL,
  `Hepatite C` int(255) DEFAULT NULL,
  `Chagas` int(255) DEFAULT NULL,
  `Sifilis` int(255) DEFAULT NULL,
  `Aids` int(255) DEFAULT NULL,
  `HTLV I` int(255) DEFAULT NULL,
  `HTLV II` int(255) DEFAULT NULL,
  `AnticorposIrregulares` int(255) DEFAULT NULL,
  `DataExame` datetime(6) DEFAULT NULL,
  `SegurancaBolsa` int(255) DEFAULT NULL,
  PRIMARY KEY (`IDExame`),
  KEY `FK4` (`IDDoador`),
  CONSTRAINT `FK4` FOREIGN KEY (`IDDoador`) REFERENCES `doadores` (`iddoador`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `exames`
--

LOCK TABLES `exames` WRITE;
/*!40000 ALTER TABLE `exames` DISABLE KEYS */;
/*!40000 ALTER TABLE `exames` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tipos sanguineos`
--

DROP TABLE IF EXISTS `tipos sanguineos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `tipos sanguineos` (
  `IDTIPO` int(255) NOT NULL,
  `Sistema ABO` varchar(255) DEFAULT NULL,
  `Sistema RH` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`IDTIPO`),
  KEY `IDTIPO` (`IDTIPO`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tipos sanguineos`
--

LOCK TABLES `tipos sanguineos` WRITE;
/*!40000 ALTER TABLE `tipos sanguineos` DISABLE KEYS */;
/*!40000 ALTER TABLE `tipos sanguineos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `triagem`
--

DROP TABLE IF EXISTS `triagem`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `triagem` (
  `IDTriagem` bigint(255) NOT NULL,
  `IDDoador` bigint(255) DEFAULT NULL,
  `SegurancaDoacao` int(255) DEFAULT NULL,
  `Anemia` int(255) DEFAULT NULL,
  `Triagem` int(255) DEFAULT NULL,
  `DataTriagem` datetime(6) DEFAULT NULL,
  PRIMARY KEY (`IDTriagem`) USING BTREE,
  KEY `SegurancaDoacao` (`SegurancaDoacao`),
  KEY `IDDoador` (`IDDoador`),
  CONSTRAINT `FK2` FOREIGN KEY (`IDDoador`) REFERENCES `doadores` (`iddoador`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `triagem`
--

LOCK TABLES `triagem` WRITE;
/*!40000 ALTER TABLE `triagem` DISABLE KEYS */;
/*!40000 ALTER TABLE `triagem` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'banco_sangue'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-11-27 23:11:08
