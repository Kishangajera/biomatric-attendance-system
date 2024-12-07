-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Dec 07, 2024 at 05:58 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `attendance_db`
--

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `sr_no` int(11) NOT NULL,
  `avd_id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `fingerprint` enum('yes','no') DEFAULT 'no'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`sr_no`, `avd_id`, `name`, `fingerprint`) VALUES
(1, 28, 'Smit Hasmukhbhai Padaliya', 'no'),
(2, 68, 'Jashpalsinh Malsinh Rathva', 'no'),
(3, 88, 'Manav Yogeshbhai Patel', 'no'),
(4, 91, 'Sanyam Dipakbhai Mistry', 'no'),
(5, 158, 'Dhruv Piyushkumar Patel', 'no'),
(6, 162, 'Yash Sanjaykumar Parekh', 'no'),
(7, 177, 'Paramkumar Vinodbhai Patel', 'no'),
(8, 185, 'Om Rajeshbhai Mokat', 'no'),
(9, 194, 'Tirthkumar Kirtibhai Patel', 'no'),
(10, 240, 'SARANG GOVINGBHAI PATEL', 'no'),
(11, 241, 'Dhaval Atulkumar Jariwala', 'no'),
(12, 243, 'Hardik Alkeshbhai Bhatt', 'no'),
(13, 267, 'Shiv Amitkumar Jariwala', 'no'),
(14, 295, 'Uttam Bharatbhai Desai', 'no'),
(15, 310, 'Sevant Prabhatbhai Desai', 'no'),
(16, 311, 'Sarveshwar Dushyanbhai Borsiwala', 'no'),
(17, 325, 'Harshal Darpan Mehta', 'no'),
(18, 338, 'Sanjaysinh Narottambhai Bariya', 'no'),
(19, 339, 'Vinitkumar Vinodbhai Patel', 'no'),
(20, 342, 'Rushikumar Ashvinbhai Patel', 'no'),
(21, 345, 'KRUTARTH ARUNSINH SOLANKI', 'no'),
(22, 353, 'Anand Kamleshbhai Patel', 'no'),
(23, 354, 'Harsh Chimanbhai Patel', 'no'),
(24, 357, 'Harshilkumar Jigneshbhai patel', 'no'),
(25, 361, 'Manan Ramjibhai Sabhaya', 'no'),
(26, 362, 'Bhargav Bharatkumar Patel', 'no'),
(27, 364, 'Ambrish DharmendraBhai Santoki', 'no'),
(28, 367, 'Parth Kiranbhai Prajapati', 'no'),
(29, 369, 'Kush Ashvinbhai Patel', 'no'),
(30, 370, 'RAKSHIT RAKESH PATEL', 'no'),
(31, 377, 'Dev Sandipbhai Patel', 'no'),
(32, 381, 'Param Kumarkant Modi', 'no'),
(33, 391, 'Harsh Chinkal Shah', 'no'),
(34, 394, 'Dhairya Mahesh Patel', 'no'),
(35, 416, 'Divyakumar Kishorbhai Patel', 'no'),
(36, 429, 'Mihir RajeshKumar Patel', 'no'),
(37, 434, 'Pruthvi Yogeshbhai Bhagat', 'no'),
(38, 436, 'Rudra Ketan bhai  Patel ', 'no'),
(39, 438, 'Gunjan  Vinodbhai  Patel ', 'no'),
(40, 443, 'Anand Manojkumar Gajjar', 'no'),
(41, 447, 'Rajmaan Kapilbhai Nakum', 'no'),
(42, 449, 'Harsh Kamleshbhai Jaggad', 'no'),
(43, 456, 'Ashish Jaiminkumar Gajjar', 'no'),
(44, 458, 'Kunjkumar Pareshkumar Patel', 'no'),
(45, 459, 'Dharmikkumar Kamleshbhai Mistry', 'no'),
(46, 461, 'Nimit Sunil Mistry', 'no'),
(47, 462, 'Priyank Anilkumar Shah', 'no'),
(48, 466, 'VAIBHAV SHANTILAL CHHABHAIYA', 'no'),
(49, 468, 'Harsh  Chetanbhai Domadia', 'no'),
(50, 469, 'Shyam Dilipbhai Viththalani', 'no'),
(51, 470, 'Harsh  Pankajkumar Patel', 'no'),
(52, 472, 'Parthiv Alpeshbhai  Patel ', 'no'),
(53, 473, 'Tanmay Sanjaybhai Chauhan', 'no'),
(54, 477, 'Krish Vasantbhai Patel', 'no'),
(55, 480, 'Samanvay Bharatsinh Solanki', 'no'),
(56, 485, 'Shubham Hareshbhai Mavani', 'no'),
(57, 486, 'Rumit Jaysukhbhai Khunt', 'no'),
(58, 488, 'Gaurav Pankajbhai Patel', 'no'),
(59, 490, 'Kushal Vrajlal Metaliya', 'no'),
(60, 491, 'Raj Maheshbhai Raninga', 'no'),
(61, 492, 'Swayam Vimalbhai Patel', 'no'),
(62, 494, 'JENIL  CHANDRESH  GANDHI ', 'no'),
(63, 501, 'Meetkumar Rajeshbhai Kankotiya', 'no'),
(64, 502, 'Jainish  Mitesh Kumar  Padariya ', 'no'),
(65, 517, 'Mihir Kamlesh bhai Shingadiya', 'no'),
(66, 518, 'NITYAM GAUTAM BHAI KHATRI', 'no'),
(67, 531, 'Het  Vijaykumar  Patel', 'no'),
(68, 536, 'saumil Hiteshbhai  patel', 'no'),
(69, 538, 'Dhruv Nikunjbhai Patel', 'no'),
(70, 543, 'ujjval pankajbhai gandhi', 'no'),
(71, 544, 'NIHAR GIRISHKUMAR JOSHI', 'no'),
(72, 551, 'Kevin  Kantilal  Vachhani ', 'no'),
(73, 555, 'PURVANG PARESHBHAI SORATHIYA', 'no'),
(74, 557, 'Vishal  Thakorbhai Patel', 'no'),
(75, 559, 'AVINASHKUMAR ASHVINBHAI BAROT', 'no'),
(76, 560, 'MEHULKUMAR  PRAVINSINH  PARMAR', 'no'),
(77, 563, 'Raaj Mahesh Chauhan', 'no'),
(78, 564, 'Jay Mahesh Chauhan', 'no'),
(79, 565, 'Nilang Atulkumar Dave', 'no'),
(80, 567, 'Sarvamkumar  Dineshkumar  Tandel ', 'no'),
(81, 568, 'GAURAV KAMLESHBHAI GHORI', 'no'),
(82, 572, 'Utsav Bharat bhai Bhanderi', 'no'),
(83, 573, 'Shreemad  Rajeshkumar  Gandhi ', 'no'),
(84, 574, 'Divyesh  Dipakbhai  Padaliya ', 'no'),
(85, 576, 'Pavitra Rakesh Bhai Shilodre', 'no'),
(86, 577, 'Param Rakeshkumar Gandhi', 'no'),
(87, 578, 'Deeptesh Maheshbhai Parmar', 'no'),
(88, 579, 'Rushikumar Harishbhai Patel', 'no'),
(89, 586, 'Virat Subhashchandra Rohit', 'no'),
(90, 587, 'Manthan Bipendra Agrawal', 'no'),
(91, 589, 'Rushi RohitBhai Patel', 'no'),
(92, 590, 'Darshan Sanjaybhai  Chauhan', 'no'),
(93, 592, 'Niraj Ashokbhai  Patel', 'no'),
(94, 594, 'RAJ KHODABHAI NAYANI', 'no'),
(95, 595, 'KENIL RAMESHBHAI NAYANI', 'no'),
(96, 597, 'Darshan Rameshbhai  Khatri ', 'no'),
(97, 598, 'Mumukshu Dharmeshbhai Patel', 'no'),
(98, 600, 'HEET BHAVESHBHAI NAYANI', 'no'),
(99, 604, 'Aaditya  Kiran Kumar  Barot', 'no'),
(100, 606, 'Sruhad Nileshbhai Patel', 'no'),
(101, 607, 'Nirav Rakesh  Kachhiya ', 'no'),
(102, 609, 'Urva Ashokbhai Gajera', 'no'),
(103, 617, 'Ravi Maheshbhai Raninga', 'no'),
(104, 620, 'manav jitendrabhai  maisuriya ', 'no'),
(105, 621, 'Aayush pareshbhai Rathod', 'no'),
(106, 622, 'Vaibhav Kiritkumar Shah', 'no'),
(107, 625, 'ARYANKUMAR  MAHESHBHAI VIDJA ', 'no'),
(108, 628, 'Nisarg Amrishbhai  Fultariya ', 'no'),
(109, 629, 'Karan  Hitesh Madhwani ', 'no'),
(110, 631, 'PARAM HARESHBHAI DHOLAKIA', 'no'),
(111, 632, 'Krish Premjibhai Dalsaniya', 'no'),
(112, 633, 'Abhaykumar  Akshaykumar  Patel', 'no'),
(113, 636, 'Kirtan Dineshbhai Rampariya', 'no'),
(114, 638, 'Nilay Vikaskumar Patel', 'no'),
(115, 643, 'Prince Vijaykumar Patel ', 'no'),
(116, 646, 'Krishna  Vijaybhai Gandhi ', 'no'),
(117, 651, 'Aditya Suresh Bhardwaj', 'no'),
(118, 655, 'Namra Jigneshkumar  Pandya', 'no'),
(119, 657, 'Dhruv Piyushkumar  Patel', 'no'),
(120, 658, 'Yash Prakashkumar Sodhaparmar', 'no'),
(121, 659, 'JAY RAJESH MISTRY', 'no'),
(122, 661, 'DHRUV SURESHBHAI PANCHASARA', 'no'),
(123, 666, 'Priyanshkumar  Rajan Bhai  Patel', 'no'),
(124, 667, 'Vansh  Dhansukhbhai Charola ', 'no'),
(125, 669, 'Keval Kalpeshbhai  Shah', 'no'),
(126, 672, 'Tirth  Jayeshchandra Chauhan', 'no'),
(127, 673, 'Smit Hasmukhbhai Fultriya', 'no'),
(128, 675, 'Harshil  Hirenkumar  Patel ', 'no'),
(129, 676, 'KRISH Nikunjkumar Gohel', 'no'),
(130, 678, 'DHRUV DHARMENDRA SOLANKI', 'no'),
(131, 680, 'Harsh Sureshbhai  Patel', 'no'),
(132, 681, 'Akshar Yogeshbhai  Patel', 'no'),
(133, 682, 'SUJAL PRAVINBHAI PATEL', 'no'),
(134, 684, 'Dharm  Ashishbhai  Trivedi ', 'no'),
(135, 685, 'Harshil  Dipakbhai Moghariya', 'no'),
(136, 686, 'PRATHAM MANOJBHAI RANGAPARIYA', 'no'),
(137, 693, 'Rakshit  Anilbhai  Sojitra ', 'no'),
(138, 694, 'Harsh  Hareshbhai Kakadiya', 'no'),
(139, 698, 'YASH MANOJBHAI  MAKADIA', 'no'),
(140, 699, 'Jitarth Swaroop Bhatt', 'no'),
(141, 700, 'Vihar Balubhai Chudasama', 'no'),
(142, 702, 'Areen  Devendra  Sharma ', 'no'),
(143, 705, 'DWIJ DHANESH VADGAMA', 'no'),
(144, 706, 'Paril Sanjaybhai  Moradiya ', 'no'),
(145, 712, 'PARSHWA MANISHKUMAR PATEL', 'no'),
(146, 716, 'Parth Tulsibhai Prajapati', 'no'),
(147, 717, 'NAYAN JAMANBHAI GOHIL', 'no'),
(148, 719, 'Nandan Vipul Bechra', 'no'),
(149, 720, 'Kirtan Kamleshbhai  Mistry', 'no'),
(150, 721, 'Prem Manojbhai  Patel', 'no'),
(151, 722, 'JAINIK NITINBHAI BHANDARI', 'no'),
(152, 724, 'Dev Ankitbhai Patel', 'no'),
(153, 726, 'Mantra  Maganbhai  Koladiya ', 'no'),
(154, 727, 'KRISH MANOJBHAI GHELANI ', 'no'),
(155, 728, 'Kavya  Yogeshkumar  Patel ', 'no'),
(156, 729, 'Mahendrasinh Bharatsinh Dodiya ', 'no'),
(157, 730, 'Dhrumilsinh Sardarsinh Rathod', 'no'),
(158, 733, 'Manavsinh Bhupatbhai  Mori', 'no'),
(159, 735, 'Dishant  Parsotambhai  Ramani', 'no'),
(160, 736, 'Vivek  Harsukhbhai  Sachdev ', 'no'),
(161, 737, 'Kishan  Mahendrabhai  Gajera ', 'no'),
(162, 738, 'SACHIN MAHENDRABHAI  GAJERA', 'no'),
(163, 741, 'Darshil  Hitesh  Bechara ', 'no'),
(164, 742, 'Prathamkumar  Miteshkumar  Patel', 'no'),
(165, 743, 'Bhavyakumar  Ashishkumar  Patel', 'no'),
(166, 744, 'Sahaj Rajnikant Patel', 'no'),
(167, 748, 'Mitansh HiteshBhai Mangukiya', 'no'),
(168, 749, 'Nirav Prashant  Gandhi', 'no'),
(169, 750, 'Vansh Shailesh bhai  Nayani', 'no'),
(170, 751, 'Neel Mukeshbhai  Umretiya ', 'no'),
(171, 752, 'Het Mukesh  Patel', 'no'),
(172, 754, 'Poojan  Pramodchandra  Patel', 'no'),
(173, 755, 'Krushitsinh Mahendrasinh Alonja', 'no'),
(174, 756, 'Harshil Kaushikbhai Patel', 'no'),
(175, 757, 'Rudra Hemantkumar Patel', 'no'),
(176, 761, 'Vivek  Sandipbhai Patel', 'no'),
(177, 762, 'Manas  Kumar  Pal ', 'no'),
(178, 768, 'TAKSH KANTIBHAI  ASALALIYA', 'no'),
(179, 769, 'Aditya Jayesh Chotalia', 'no'),
(180, 770, 'Garvin Hiteshbhai Vasani', 'no'),
(181, 771, 'Devansh Sunil Chanpura', 'no'),
(182, 772, 'Herit Vipulbhai  Usadadiya ', 'no'),
(183, 773, 'Arpan Hareshkumar  Patel', 'no'),
(184, 774, 'Smit Dashrathbhai  Mahida', 'no'),
(185, 775, 'Dip Ketanbhai Baldha', 'no'),
(186, 776, 'Raj  Bhupendrabhai  Ghoniya', 'no'),
(187, 779, 'Sudhir Ajay Dubey', 'no'),
(188, 780, 'Mohit Vikas Bhatia', 'no'),
(189, 781, 'Krishna Sanjaybhai Baigani', 'no'),
(190, 782, 'Devvrat Bharat Kumar  Padshala', 'no'),
(191, 787, 'Kushagra  Keshavlalit Ameta', 'no'),
(192, 788, 'Pratikbhai Shanmukhbhai Vasava', 'no'),
(193, 789, 'Yash Nileshbhai Vaghasiya', 'no'),
(194, 790, 'Pavitra Jagdishbhai Patel', 'no'),
(195, 791, 'Aryan Rakesh Kanada', 'no'),
(196, 792, 'Aaditya  Gautam  Purohit', 'no'),
(197, 793, 'Joy Falgunkumar  Patel', 'no'),
(198, 794, 'Kunj Sanjay bhai Dhameliya ', 'no'),
(199, 795, 'Krushna Praduman Hansoti', 'no'),
(200, 797, 'Vineet Bhupesh Rathod', 'no'),
(201, 798, 'Hardikkumar  Sitanshubhai  Patel', 'no'),
(202, 799, 'Aaryan Indra bhan Shrimali', 'no'),
(203, 800, 'SHIVAM RAJESHBHAI Ghetia', 'no'),
(204, 801, 'Het Prakashbhai Patel', 'no'),
(205, 802, 'NISARG  SATISHBHAI  DETROJA', 'no'),
(206, 804, 'Het Tejaskumar Patel', 'no'),
(207, 805, 'Zeel PinalKumar  Kachhia', 'no'),
(208, 807, 'Meet  Sanjay Kumar  Patel', 'no'),
(209, 808, 'Jainil Jayeshbhai Patel', 'no'),
(210, 812, 'Bhargav Ashok Panchal', 'no'),
(211, 813, 'Rudra Amitbhai Patel', 'no'),
(212, 814, 'Nevil Dilipkumar  Makasana', 'no'),
(213, 815, 'Zeel  Chandreshbhai Patel', 'no'),
(214, 819, 'Aditya Sagar Jetly', 'no'),
(215, 820, 'Hari Vijaykumar  Patel', 'no'),
(216, 822, 'Meetraj  Dilubhai  Boricha', 'no'),
(217, 823, 'Vraj Nileshkumar  Patel', 'no'),
(218, 824, 'Harsh Durgeshkumar  Varia', 'no'),
(219, 825, 'Meet Hirenbhai  Modi', 'no'),
(220, 826, 'Gunjan Dhaval Patel', 'no'),
(221, 828, 'RAHUL RAVABHAI NADODA', 'no'),
(222, 829, 'Sujal Shaileshbhai  Kardani ', 'no'),
(223, 830, 'Harshrajsinh Rajendrasinh Kathvadiya', 'no'),
(224, 831, 'Het Hiralbhai  Patel', 'no'),
(225, 832, 'Abhishek  Jaydeepbhai  Bhadiyadra ', 'no'),
(226, 834, 'Samanvay Chandrakantbhai  Patel', 'no'),
(227, 837, 'JEEL AMITKUMAR PATEL', 'no'),
(228, 838, 'Jinil  Pareshkumar  Patel', 'no'),
(229, 839, 'Vraj Hiteshbhai  Patel', 'no'),
(230, 840, 'Swayam  Bhavesh Bhai  Raiyani', 'no'),
(231, 841, 'Adityarajsinh Digvijaysinh Gohil', 'no'),
(232, 842, 'Meet Vipulbhai Rana', 'no'),
(233, 843, 'SAMARTH AKILKUMAR GANDHI', 'no'),
(234, 844, 'Mihir Narsinhbhai Tank', 'no'),
(235, 845, 'Harsh Rajendra Ajmera', 'no'),
(236, 847, 'KARANSINH  RANJITSINH MORI', 'no'),
(237, 848, 'Viraj  Hasmukhbhai Moghariya ', 'no'),
(238, 849, 'Meet Taleshkumar  Gandhi', 'no'),
(239, 850, 'Harpal Nanalal Bhoraniya ', 'no'),
(240, 851, 'Harikrushn Girish  Poriya', 'no'),
(241, 852, 'Viral  Jayeshbhai Mistry ', 'no'),
(242, 853, 'Keyur Jayeshbhai Mistry', 'no'),
(243, 855, 'Maan Mitulbhai  Patel', 'no'),
(244, 856, 'Nisarg Divyeshbhai Patel ', 'no'),
(245, 857, 'Nirman Jayeshbhai Sutariya', 'no'),
(246, 858, 'Harsh  Ajaykumar  Tailor ', 'no'),
(247, 859, 'Het Pareshbhai Savani', 'no'),
(248, 860, 'Mrudul Hiteshbhai Dhaduk', 'no'),
(249, 861, 'Nisarg Manishbhai Kamaria', 'no'),
(250, 862, 'Jeel Ajaybhai Satani', 'no'),
(251, 863, 'Jenil  Jitendrabhai Rank', 'no'),
(252, 864, 'Bhavya Mukeshbhai Patel', 'no'),
(253, 865, 'Yagnik  Rajeshkumar  Patel', 'no'),
(254, 866, 'Smit  Kiritbhai Joshi ', 'no'),
(255, 867, 'Jaygiri Bhaveshgiri Goswami', 'no'),
(256, 869, 'Kavya Vipulbhai Kakadiya', 'no'),
(257, 870, 'Malhar  Jignesh Joshi', 'no'),
(258, 871, 'Gaurav Pradeep Kumar', 'no'),
(259, 872, 'Chitrang Rajesh Upadhyay', 'no'),
(260, 873, 'AADHYA VIJAYKUMAR DAVE', 'no'),
(261, 874, 'Kirtankumar  Priteshbhai Patel', 'no'),
(262, 875, 'Mantra Janardan Rajyaguru ', 'no'),
(263, 876, 'Aadi Niraj Pandya', 'no'),
(264, 877, 'Harin Jatinbhai Patel', 'no'),
(265, 878, 'Vatsal Niranjanbhai Patel', 'no'),
(266, 879, 'Neel Chandubhai  Arvadiya ', 'no'),
(267, 880, 'Rudra Atulbhai Gondaliya', 'no'),
(268, 881, 'Om  Chetanbhai  Sutariya', 'no'),
(269, 882, 'Mayank Chunilal  Kaila', 'no'),
(270, 883, 'Shashwat Somabhai Prajapati', 'no'),
(271, 884, 'Sujal Sundeep Saraiya', 'no'),
(272, 886, 'Vasu Hasmukhbhai Makhasana', 'no'),
(273, 887, 'Rudra Piyushbhai Mangaroliya', 'no'),
(274, 888, 'Ayush Ramubhai Ahir', 'no'),
(275, 889, 'Rudrakumar Anilbhai  Patel', 'no'),
(276, 890, 'Nemish Hiteshbhai  Ghori', 'no'),
(277, 892, 'parv prashant kumar bhatt', 'no'),
(278, 893, 'Manan Bharatbhai  Vasani', 'no'),
(279, 894, 'Dhairya Maheshbhai Jivani', 'no'),
(280, 895, 'Shreykumar  Dalsukhbhai  Patel', 'no'),
(281, 896, 'Adarsh Mukeshbhai kanani', 'no'),
(282, 897, 'Fenil  Chandubhai Rupapara', 'no'),
(283, 898, 'Meet Virendra  Patel', 'no'),
(284, 899, 'Siddh Bharatkumar  Patel', 'no'),
(285, 900, 'Heet Maheshbhai  Rupapara ', 'no'),
(286, 901, 'Ansh Kiranbhai  Davra', 'no'),
(287, 902, 'Sriharsh Ashok Chintakindi', 'no'),
(288, 903, 'Om Shambhuprasad  Joshi', 'no'),
(289, 904, 'Dhruv Kishorbhai Jasani', 'no'),
(290, 905, 'Sneh Arvindbhai Shingala', 'no'),
(291, 906, 'Manthan Dharmesh Bhalara', 'no'),
(292, 907, 'Shivang Shaileshkumar Patel', 'no'),
(293, 908, 'Jatin Amit  Bodhe', 'no'),
(294, 909, 'KUNJ DHARMENDRA PATEL', 'no'),
(295, 910, 'Pruthvi  Munnabhai Sharma', 'no'),
(296, 911, 'Harsh  Maheshbhai  Gohil ', 'no'),
(297, 912, 'Het Sanjaybhai  Vanani', 'no'),
(298, 913, 'Divyesh  Shailesh  Patel', 'no'),
(299, 915, 'Meet Vijaybhai  Gajera', 'no'),
(300, 917, 'VRAJ TUSHAR PANCHAL', 'no'),
(301, 918, 'VEDANT KALPESHKUMAR DARJI', 'no'),
(302, 919, 'Mayur Mallikarjun Kachhadiya', 'no'),
(303, 920, 'Kunj Bharatbhai Patel', 'no'),
(304, 921, 'Dhruv  Girishbhai  Bhimani', 'no'),
(305, 922, 'Vidhang  Sanjay Mundra', 'no'),
(306, 923, 'Heet Bhaveshbhai  Kansagara ', 'no'),
(307, 924, 'Prince Jayeshbhai Desai', 'no'),
(308, 925, 'Tirth Hareshbhai Gevariya', 'no'),
(309, 926, 'Ansh Arvindbhai Gevariya', 'no'),
(310, 927, 'Parshva Ashokbhai Patel', 'no'),
(311, 928, 'Vraj Sanjaybhai Patel', 'no'),
(312, 929, 'Yug  Hiteshbhai  Dadhania ', 'no'),
(313, 930, 'Dev Rameshbhai Patel', 'no'),
(314, 932, 'Harsh Harishbhai  Surati', 'no'),
(315, 933, 'Pavitra Bhaveshbhai Mevawala', 'no'),
(316, 934, 'Kirtankumar  Mahendrasinh  Padhiyar ', 'no'),
(317, 935, 'Aniket Bipinbhai Parmar ', 'no'),
(318, 936, 'Renish  Hiteshbhai  Bhavani', 'no'),
(319, 937, 'Laksh Sandeepkumar maisuria', 'no'),
(320, 938, 'Mahir Jigneshbhai Motani', 'no'),
(321, 939, 'Anand Surendra bhai Solanki ', 'no'),
(322, 940, 'Kush Hiteshbhai  Patel', 'no'),
(323, 941, 'Khush Ketanbhai Gol', 'no'),
(324, 942, 'Parth Kumarbhai Solanki', 'no'),
(325, 943, 'DEVAM HETALBHAI PATEL', 'no');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
