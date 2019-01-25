{
  'targets': [
    {
      'target_name': 'clipboard',
      'type': 'executable',
      'sources': [],
      'conditions': [
        ['OS == "linux"', {
          'sources': [
             'clipboard/cpb_linux.cc',
          ]
        }],
        ['OS == "mac"', {
          'sources': [
             'clipboard/cpb_mac.cc',
          ]
        }],
        ['OS == "win"', {
          'sources': [
             'clipboard/cpb_win.cc',
          ]
        }],
      ],
      'include_dirs': [
        '<!(node -e \'require("nan")\')'
      ],
    },
  ],
}