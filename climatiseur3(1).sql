-- phpMyAdmin SQL Dump
-- version 4.0.4
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le: Jeu 22 Mai 2014 à 09:55
-- Version du serveur: 5.6.12-log
-- Version de PHP: 5.4.16

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données: `climatiseur3`
--
CREATE DATABASE IF NOT EXISTS `climatiseur3` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `climatiseur3`;

-- --------------------------------------------------------

--
-- Structure de la table `t_campagnedemesure`
--

CREATE TABLE IF NOT EXISTS `t_campagnedemesure` (
  `id_CampagneDeMesure` int(11) NOT NULL AUTO_INCREMENT,
  `nom` varchar(15) DEFAULT NULL,
  `date` datetime DEFAULT NULL,
  `machine` varchar(15) DEFAULT NULL,
  `emplacement` varchar(15) DEFAULT NULL,
  `echantillonnage` int(11) DEFAULT NULL,
  `commentaire` text,
  PRIMARY KEY (`id_CampagneDeMesure`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=36 ;

-- --------------------------------------------------------

--
-- Structure de la table `t_mesure`
--

CREATE TABLE IF NOT EXISTS `t_mesure` (
  `id_mesure` int(11) NOT NULL AUTO_INCREMENT,
  `numero_mesure` int(11) DEFAULT NULL,
  `hygrometrie` int(11) DEFAULT NULL,
  `temperature` int(11) DEFAULT NULL,
  `temperature_ambiante` int(11) DEFAULT NULL,
  `temperature_souflage_aire` int(11) DEFAULT NULL,
  `temperature_sortie_aire` int(11) DEFAULT NULL,
  `temperature aspiration` int(11) DEFAULT NULL,
  `temperature refoulement` int(11) DEFAULT NULL,
  `temperature_sortie_evaporateur` int(11) DEFAULT NULL,
  `temperature_entree_evaporateur` int(11) DEFAULT NULL,
  `temperature_sortie_detendeur` int(11) DEFAULT NULL,
  `temperature_sortie_condenseur` int(11) DEFAULT NULL,
  `temperature_entree_condenseur` int(11) DEFAULT NULL,
  `tension_alimentation` int(11) DEFAULT NULL,
  `courant` int(11) DEFAULT NULL,
  `puissance` int(11) DEFAULT NULL,
  `anemometre` int(11) DEFAULT NULL,
  `ExtId_CampagneDeMesure` int(11) DEFAULT NULL,
  PRIMARY KEY (`id_mesure`),
  KEY `fk_t_mesure_t_campagnedemesure_idx` (`ExtId_CampagneDeMesure`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Contraintes pour les tables exportées
--

--
-- Contraintes pour la table `t_mesure`
--
ALTER TABLE `t_mesure`
  ADD CONSTRAINT `fk_t_mesure_t_campagnedemesure` FOREIGN KEY (`ExtId_CampagneDeMesure`) REFERENCES `t_campagnedemesure` (`id_CampagneDeMesure`) ON DELETE NO ACTION ON UPDATE NO ACTION;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
