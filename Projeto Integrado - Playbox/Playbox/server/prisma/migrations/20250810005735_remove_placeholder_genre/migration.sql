/*
  Warnings:

  - The values [PLACEHOLDER] on the enum `Genre` will be removed. If these variants are still used in the database, this will fail.

*/
-- AlterEnum
BEGIN;
CREATE TYPE "Genre_new" AS ENUM ('ACTION', 'ADVENTURE', 'INDIE', 'MASSIVELY_MULTIPLAYER', 'PLATFORMER', 'PUZZLE', 'RPG', 'RACING', 'SHOOTER', 'SPORTS');
ALTER TYPE "Genre" RENAME TO "Genre_old";
ALTER TYPE "Genre_new" RENAME TO "Genre";
DROP TYPE "Genre_old";
COMMIT;
