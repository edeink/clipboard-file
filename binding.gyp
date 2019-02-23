{
  'targets': [
    {
      'target_name': 'clipboard',
      'sources': [],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
      'conditions': [
        ['OS == "linux"', {
          'sources': [
             'clipboard/cpb_linux.cc',
          ]
        }],
        ['OS == "mac"', {
          'sources': [
             'clipboard/cpb_mac.mm',
          ],
	  'libraries': [
             '-framework AppKit',
	  ]
        }],
        ['OS == "win"', {
          'sources': [
             'clipboard/cpb_win.cc',
          ],
        }],
      ],
    },
  ],
}
