/*
  Warnings:

  - You are about to drop the column `genre` on the `Catalog` table. All the data in the column will be lost.
  - Made the column `metacriticScore` on table `Game` required. This step will fail if there are existing NULL values in that column.

*/
-- AlterTable
ALTER TABLE "Catalog" DROP COLUMN "genre";

-- AlterTable
ALTER TABLE "Game" ALTER COLUMN "metacriticScore" SET NOT NULL;
