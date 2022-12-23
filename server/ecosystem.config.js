module.exports = {
    apps: [
        {
            name: 'camera server',
            script: './server.js',
            env: {
                // NODE_ENV: 'development',
                PORT: 59182,
            },
            watch: true,
        },
    ],
};
