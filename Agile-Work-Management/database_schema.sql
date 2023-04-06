-- Create the database and set the default character set
CREATE DATABASE IF NOT EXISTS kanban_agile_work_management;
USE kanban_agile_work_management;
SET NAMES utf8mb4;
​
-- Create the table for storing the projects
CREATE TABLE IF NOT EXISTS projects (
  project_id INT NOT NULL AUTO_INCREMENT,
  project_name VARCHAR(255) NOT NULL,
  PRIMARY KEY (project_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
​
​
-- Create the table for storing the Kanban boards
CREATE TABLE IF NOT EXISTS kanban_boards (
  board_id INT NOT NULL AUTO_INCREMENT,
  board_name VARCHAR(255) NOT NULL,
  project_id INT NOT NULL,
  start_date DATE,
  end_date DATE,
  PRIMARY KEY (board_id),
  FOREIGN KEY (project_id) REFERENCES projects(project_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
​
-- Create the table for storing the Kanban board columns
CREATE TABLE IF NOT EXISTS kanban_columns (
  column_id INT NOT NULL AUTO_INCREMENT,
  column_name VARCHAR(255) NOT NULL,
  board_id INT NOT NULL,
  column_position INT NOT NULL,
  PRIMARY KEY (column_id),
  FOREIGN KEY (board_id) REFERENCES kanban_boards(board_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
​
-- Create the table for storing the users
CREATE TABLE IF NOT EXISTS users (
  user_id INT NOT NULL AUTO_INCREMENT,
  user_name VARCHAR(255) NOT NULL,
  full_name VARCHAR(255) NOT NULL,
  user_email VARCHAR(255) NOT NULL,
  role VARCHAR(255),
  PRIMARY KEY (user_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
​
-- Create the table for storing the issue types
CREATE TABLE IF NOT EXISTS issue_types (
  issue_type_id INT NOT NULL AUTO_INCREMENT,
  issue_type_name VARCHAR(255) NOT NULL,
  PRIMARY KEY (issue_type_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
​
-- Create the table for storing the issues
CREATE TABLE IF NOT EXISTS issues (
  issue_id INT NOT NULL AUTO_INCREMENT,
  summary VARCHAR(255) NOT NULL,
  description TEXT,
  status VARCHAR(255) NOT NULL,
  priority VARCHAR(255) NOT NULL,
  assignee INT,
  project_id INT NOT NULL,
  issue_type INT NOT NULL,
  column_id INT NOT NULL,
  estimate FLOAT,
  PRIMARY KEY (issue_id),
  FOREIGN KEY (assignee) REFERENCES users(user_id),
  FOREIGN KEY (project_id) REFERENCES projects(project_id),
  FOREIGN KEY (issue_type) REFERENCES issue_types(issue_type_id),
  FOREIGN KEY (column_id) REFERENCES kanban_columns(column_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;