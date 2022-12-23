const express = require('express');
const multer = require('multer');
const fs = require('fs');

const app = express();

const port = process.env.PORT || 3000;

// if it doesn't exist, create uploads folder
const dir = './uploads';
if (!fs.existsSync(dir)) {
    fs.mkdirSync(dir);
}

// Set up the multer middleware to handle file uploads
const storage = multer.diskStorage({
    destination: function (req, file, cb) {
        cb(null, dir);
    },
    filename: function (req, file, cb) {
        let name = `${new Date().toISOString()}-${file.originalname}`;
        let additional = 1;

        // if file exists, add -1, -2, -3, etc. to the end of the filename
        if (fs.existsSync(dir + '/' + name)) {
            while (fs.existsSync(dir + '/' + name + '-' + additional))
                additional++;
            name = name + '-' + additional;
        }

        cb(null, name);
    },
});

const upload = multer({storage: storage});

// log all requests
app.use((req, res, next) => {
    console.log(req.method, req.url);
    next();
});

app.post('/api/upload', upload.single('data'), (req, res) => {
    if (!req.file) {
        return res.status(400).send('No file was uploaded.');
    }
    res.status(201).send(
        'File uploaded and saved successfully at ' + req.file.path,
    );
});

app.listen(port, () => {
    console.log('Server listening on port', port);
});
