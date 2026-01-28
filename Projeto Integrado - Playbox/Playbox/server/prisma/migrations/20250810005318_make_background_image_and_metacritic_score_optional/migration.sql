-- AlterTable
ALTER TABLE "Game" ALTER COLUMN "backgroundImage" DROP NOT NULL,
ALTER COLUMN "playtime" SET DEFAULT 0,
ALTER COLUMN "metacriticScore" DROP NOT NULL;
