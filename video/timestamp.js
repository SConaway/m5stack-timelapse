const Jimp = require('jimp');
const fs = require('fs');
const moment = require('moment-timezone');
const promisify = require('util').promisify;

const inputDir = '../images/input';
const outputDir = '../images/ts';

// Create the output directory if it doesn't exist
if (!fs.existsSync(outputDir)) {
    fs.mkdirSync(outputDir);
}
// Remove all files from the output directory
fs.readdirSync(outputDir).forEach((file) => {
    fs.unlinkSync(`${outputDir}/${file}`);
});

// Promisify the fs.readdir and Jimp.read functions
const readdir = promisify(fs.readdir);
const readImage = promisify(Jimp.read);

async function processImage(file, font) {
    const fileParts = file.split('camera.jpg');
    const isoTimestamp = fileParts[0];
    const timestamp = moment
        .tz(isoTimestamp, 'YYYY-MM-DDTHH:mm:ss.sssZ', 'UTC')
        .tz('America/Boise');

    // Read the image using Jimp
    const image = await readImage(`${inputDir}/${file}`);

    // Get the image dimensions
    const imageWidth = image.bitmap.width;
    const imageHeight = image.bitmap.height;

    // Add the timestamp to the lower-right corner of the image
    image.print(
        font,
        imageWidth - 260,
        imageHeight - 40,
        timestamp.format('MM/DD/YYYY HH:mm'),
    );

    // Save the modified image to the output directory
    image.write(`${outputDir}/${file}`);
}

async function main() {
    try {
        const font = await Jimp.loadFont('opensans-light-32-white.fnt');
        // Read all files in the input directory
        const files = await readdir(inputDir);

        // Iterate over each file in the directory
        for (const file of files) {
            // Parse the timestamp from the filename
            await processImage(file, font);
        }
    } catch (error) {
        console.error(error);
    }
}

// Run the main function
main();
