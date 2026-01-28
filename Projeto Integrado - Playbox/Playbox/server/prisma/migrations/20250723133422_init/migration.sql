-- CreateEnum
CREATE TYPE "Genre" AS ENUM ('ACTION', 'ADVENTURE', 'INDIE', 'MASSIVELY_MULTIPLAYER', 'PLATFORMER', 'PUZZLE', 'RPG', 'RACING', 'SHOOTER', 'SPORTS', 'PLACEHOLDER');

-- CreateTable
CREATE TABLE "User" (
    "id" SERIAL NOT NULL,
    "name" TEXT NOT NULL,
    "email" TEXT NOT NULL,
    "password" TEXT NOT NULL,
    "isAdmin" BOOLEAN NOT NULL DEFAULT false,
    "createdAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updatedAt" TIMESTAMP(3) NOT NULL,

    CONSTRAINT "User_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "Review" (
    "id" SERIAL NOT NULL,
    "userId" INTEGER NOT NULL,
    "gameId" INTEGER NOT NULL,
    "gameplayRating" INTEGER NOT NULL,
    "visualRating" INTEGER NOT NULL,
    "audioRating" INTEGER NOT NULL,
    "difficultyRating" INTEGER NOT NULL,
    "immersionRating" INTEGER NOT NULL,
    "historyRating" INTEGER NOT NULL,
    "averageRating" DOUBLE PRECISION NOT NULL,
    "comment" TEXT,
    "createdAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updatedAt" TIMESTAMP(3) NOT NULL,

    CONSTRAINT "Review_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "Game" (
    "id" SERIAL NOT NULL,
    "name" TEXT NOT NULL,
    "releaseDate" DATE NOT NULL,
    "description" TEXT,
    "backgroundImage" TEXT NOT NULL,
    "playtime" INTEGER NOT NULL,
    "platforms" TEXT NOT NULL,
    "genres" TEXT NOT NULL,
    "publishers" TEXT NOT NULL,
    "metacriticScore" INTEGER,
    "averageReviewRating" DOUBLE PRECISION,
    "screenshots" TEXT NOT NULL,
    "createdAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updatedAt" TIMESTAMP(3) NOT NULL,

    CONSTRAINT "Game_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "Catalog" (
    "id" SERIAL NOT NULL,
    "name" TEXT NOT NULL,
    "userId" INTEGER,
    "genre" "Genre",
    "createdAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updatedAt" TIMESTAMP(3) NOT NULL,

    CONSTRAINT "Catalog_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "_GameCatalogs" (
    "A" INTEGER NOT NULL,
    "B" INTEGER NOT NULL,

    CONSTRAINT "_GameCatalogs_AB_pkey" PRIMARY KEY ("A","B")
);

-- CreateIndex
CREATE UNIQUE INDEX "User_name_key" ON "User"("name");

-- CreateIndex
CREATE UNIQUE INDEX "User_email_key" ON "User"("email");

-- CreateIndex
CREATE UNIQUE INDEX "Game_name_key" ON "Game"("name");

-- CreateIndex
CREATE UNIQUE INDEX "Catalog_name_key" ON "Catalog"("name");

-- CreateIndex
CREATE INDEX "_GameCatalogs_B_index" ON "_GameCatalogs"("B");

-- AddForeignKey
ALTER TABLE "Review" ADD CONSTRAINT "Review_userId_fkey" FOREIGN KEY ("userId") REFERENCES "User"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Review" ADD CONSTRAINT "Review_gameId_fkey" FOREIGN KEY ("gameId") REFERENCES "Game"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Catalog" ADD CONSTRAINT "Catalog_userId_fkey" FOREIGN KEY ("userId") REFERENCES "User"("id") ON DELETE SET NULL ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "_GameCatalogs" ADD CONSTRAINT "_GameCatalogs_A_fkey" FOREIGN KEY ("A") REFERENCES "Catalog"("id") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "_GameCatalogs" ADD CONSTRAINT "_GameCatalogs_B_fkey" FOREIGN KEY ("B") REFERENCES "Game"("id") ON DELETE CASCADE ON UPDATE CASCADE;
