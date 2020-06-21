builtin.log('hello from entry.js');

builtin.include('tonal.min.js');

builtin.log('a4 midi is:', Tonal.Note.midi('A4'));

const af = async () => builtin.log('an async function');
(async () => {
    builtin.log('A');
    await af();
    builtin.log('B');
})();
builtin.log('if async works, i will be between A and B. probably.');

'and this is the returned value.'
