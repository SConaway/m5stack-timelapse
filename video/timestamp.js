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
// fs.readdirSync(outputDir).forEach((file) => {
//     fs.unlinkSync(`${outputDir}/${file}`);
// });
const currentFiles = fs.readdirSync(outputDir);

// Promisify the fs.readdir and Jimp.read functions
const readdir = promisify(fs.readdir);
const readImage = promisify(Jimp.read);

async function processImage(file, font) {
    // parse the timestamp from the filename
    const fileParts = file.split('camera.jpg');
    const isoTimestamp = fileParts[0];
    // Convert the timestamp to the local timezone
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

        // print number being skipped and number being processed
        let done = currentFiles.length;
        let left = files.length - done;
        console.log(`Skipping ${done} files`);
        console.log(`Processing ${left} files`);

        // Iterate over each file in the directory
        for (const file of files) {
            // if file already exists, skip
            if (currentFiles.includes(file)) {
                // console.log(`Skipping ${file} - already exists`);
                continue;
            }

            // Skip any files that don't end with camera.jpg
            if (!file.endsWith('camera.jpg')) {
                console.log(`Skipping ${file} - not a camera image`);
                continue;
            }

            // Process the image
            // console.log(`Processing ${file}`);
            try {
                await processImage(file, font);
            } catch (error) {
                console.error(`Error processing ${file}: ${error}`);
            }

            // print number done and number left every 100 files
            done++;
            left--;
            if (done % 100 === 0) {
                console.log(
                    `Progress: ${done} / ${files.length} (${left} left)`,
                );
            }
        }
    } catch (error) {
        console.error(error);
    }
}

// Run the main function
main();
