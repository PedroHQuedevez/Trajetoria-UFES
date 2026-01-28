module.exports = {
  testEnvironment: 'node',
  collectCoverage: false,
  testMatch: [
    "**/__tests__/**/*.js",
    "**/?(*.)+(spec|test).js"
  ],
  setupFilesAfterEnv: ['<rootDir>/__tests__/setup.js'],
  testPathIgnorePatterns: [
    "/node_modules/",
    "/__tests__/setup.js"
  ],
  coverageDirectory: 'coverage',
  coverageReporters: ['text', 'lcov', 'html'],
  collectCoverageFrom: [
    'routes/**/*.js',
    'services/**/*.js',
    '!services/prisma.js',
    '!**/node_modules/**'
  ],
  verbose: true,
  forceExit: true,
  clearMocks: true
};
