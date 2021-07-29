/*
 Navicat Premium Data Transfer

 Source Server         : archeage
 Source Server Type    : MySQL
 Source Server Version : 80012
 Source Host           : localhost:3306
 Source Schema         : alocacao_salas

 Target Server Type    : MySQL
 Target Server Version : 80012
 File Encoding         : 65001

 Date: 22/11/2018 16:47:29
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for alocacao
-- ----------------------------
DROP TABLE IF EXISTS `alocacao`;
CREATE TABLE `alocacao`  (
  `IDAlocacao` int(11) NOT NULL AUTO_INCREMENT,
  `DataAlocacao` date NULL DEFAULT NULL,
  `DataInicio` date NULL DEFAULT NULL,
  `DataTermino` date NULL DEFAULT NULL,
  `HoraInicio` time(0) NULL DEFAULT NULL,
  `HoraTermino` time(0) NULL DEFAULT NULL,
  `DiaSemana` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `IDEvento` int(11) NOT NULL,
  `IDSala` int(11) NOT NULL,
  `IDFuncionario` int(11) NOT NULL,
  PRIMARY KEY (`IDAlocacao`) USING BTREE,
  INDEX `IDEvento`(`IDEvento`) USING BTREE,
  INDEX `IDSala`(`IDSala`) USING BTREE,
  INDEX `IDFuncionario`(`IDFuncionario`) USING BTREE,
  CONSTRAINT `alocacao_ibfk_1` FOREIGN KEY (`IDEvento`) REFERENCES `evento` (`idevento`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `alocacao_ibfk_2` FOREIGN KEY (`IDSala`) REFERENCES `sala` (`idsala`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `alocacao_ibfk_3` FOREIGN KEY (`IDFuncionario`) REFERENCES `funcionario` (`idfuncionario`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for curso
-- ----------------------------
DROP TABLE IF EXISTS `curso`;
CREATE TABLE `curso`  (
  `IDCurso` int(11) NOT NULL AUTO_INCREMENT,
  `Nome` varchar(150) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Sigla` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `CargaHoraria` time(0) NULL DEFAULT NULL,
  `IDDepartamento` int(11) NOT NULL,
  PRIMARY KEY (`IDCurso`) USING BTREE,
  INDEX `IDDepartamento`(`IDDepartamento`) USING BTREE,
  CONSTRAINT `curso_ibfk_1` FOREIGN KEY (`IDDepartamento`) REFERENCES `departamento` (`iddepartamento`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for departamento
-- ----------------------------
DROP TABLE IF EXISTS `departamento`;
CREATE TABLE `departamento`  (
  `IDDepartamento` int(11) NOT NULL AUTO_INCREMENT,
  `Nome` varchar(150) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Sigla` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`IDDepartamento`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for endereco
-- ----------------------------
DROP TABLE IF EXISTS `endereco`;
CREATE TABLE `endereco`  (
  `IDEndereco` int(11) NOT NULL AUTO_INCREMENT,
  `UF` char(2) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Cidade` varchar(150) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Bairro` varchar(150) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Rua` varchar(150) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `CEP` char(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`IDEndereco`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for evento
-- ----------------------------
DROP TABLE IF EXISTS `evento`;
CREATE TABLE `evento`  (
  `IDEvento` int(11) NOT NULL AUTO_INCREMENT,
  `Nome` varchar(150) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Descricao` varchar(300) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Sigla` char(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`IDEvento`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for funcionario
-- ----------------------------
DROP TABLE IF EXISTS `funcionario`;
CREATE TABLE `funcionario`  (
  `IDFuncionario` int(11) NOT NULL AUTO_INCREMENT,
  `Nome` varchar(150) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `CPF` char(14) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Email` varchar(150) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `DataAdmissao` date NULL DEFAULT NULL,
  `DataDemissao` date NULL DEFAULT NULL,
  `Salario` decimal(12, 2) NULL DEFAULT NULL,
  `IDDepartamento` int(11) NOT NULL,
  `IDEndereco` int(11) NOT NULL,
  PRIMARY KEY (`IDFuncionario`) USING BTREE,
  INDEX `IDEndereco`(`IDEndereco`) USING BTREE,
  INDEX `IDDepartamento`(`IDDepartamento`) USING BTREE,
  CONSTRAINT `funcionario_ibfk_1` FOREIGN KEY (`IDEndereco`) REFERENCES `endereco` (`idendereco`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `funcionario_ibfk_2` FOREIGN KEY (`IDDepartamento`) REFERENCES `departamento` (`iddepartamento`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for sala
-- ----------------------------
DROP TABLE IF EXISTS `sala`;
CREATE TABLE `sala`  (
  `IDSala` int(11) NOT NULL AUTO_INCREMENT,
  `Sigla` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `TipoSala` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Capacidade` int(11) NULL DEFAULT NULL,
  `IDDepartamento` int(11) NOT NULL,
  PRIMARY KEY (`IDSala`) USING BTREE,
  INDEX `IDDepartamento`(`IDDepartamento`) USING BTREE,
  CONSTRAINT `sala_ibfk_1` FOREIGN KEY (`IDDepartamento`) REFERENCES `departamento` (`iddepartamento`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
